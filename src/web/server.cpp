#include "server.h"
#include "../util/status.h"
#include "../util/common.h"

int server_port;
int web_sock;
int epoll_fd;
struct epoll_event event;


void init_server_web(){
    if((epoll_fd = epoll_create1(0)) == -1){
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    event.events = EPOLLIN | EPOLLRDHUP;
    web_sock = socket(AF_INET,SOCK_STREAM,0);
    if(web_sock == -1){
        perror("Socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in web_addr;
    web_addr.sin_family = AF_INET;
    web_addr.sin_addr.s_addr = INADDR_ANY;
    web_addr.sin_port = htons((uint16_t) server_port);

    if(bind(web_sock,(struct sockaddr *)&web_addr,sizeof(web_addr)) == -1){
        perror("Bind");
        exit(EXIT_FAILURE);
    }
    if(listen(web_sock,N) == -1){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    event.data.fd = web_sock;
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, web_sock, &event)==-1){
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }
}


void server_stop(){
    close(epoll_fd);
    shutdown(web_sock,SHUT_RDWR);
    close(web_sock);
}

void server_quit(int sig){
    exit(EXIT_SUCCESS);
}

void server_push(int fd, Msg msg) {
    Vector<String> client_hashes = msgToStrings(msg.buf2);
    Vector<String> server_hashes = read_all_lines(HEAD.c_str());
    int i = 0;
    int j = 0;
    while(i < client_hashes.size() && j < server_hashes.size()){
        if(client_hashes[i] == server_hashes[i]){
            i++;
            j++;
        }
        else{
            msg.type = MSG_END;
            send(fd,&msg,sizeof(msg),0);
            return;
        }
    }
    if(i < client_hashes.size()){
        if(i == 0){
            strcpy(msg.buf2,"");
        }
        else{
            strcpy(msg.buf2,client_hashes[i-1].c_str());
        }
        while(i < client_hashes.size()){
            String s = COMMITS_DIR + "/" +  deleteEndl(client_hashes[i]);
            mkdir(s.c_str(),DEFAULT_PERM);
            i++;
        }
        send(fd,&msg,sizeof(msg),0);
        if(recv(fd, &msg, sizeof(msg), MSG_WAITALL) == -1){
            perror("recv");
            exit(EXIT_FAILURE);
        }
        while(msg.type != MSG_END){
            printf("%s\n",msg.buf);
            FILE * file = fopen(msg.buf,"w");
            fprintf(file,"%s",msg.buf2);
            fclose(file);
            if(recv(fd, &msg, sizeof(msg), MSG_WAITALL) == -1){
                perror("recv");
                exit(EXIT_FAILURE);
            }
        }
        String dir = COMMITS_DIR + "/" + deleteEndl(last_commit_hash()) + "/";
        Vector<String> files = ls(dir.c_str());
        for(int k = 0; k < files.size();k++){
            String source = dir + files[k];
            Cout << source << Endl;
            String destination = STAGE_DIR + "/" + files[k];
            copy(source.c_str(),destination.c_str());
            destination = "./" + files[k];
            copy(source.c_str(),destination.c_str());
        }
    }
}

void server_pull(int fd, Msg msg) {
    fileToMsg(HEAD,msg);
    msg.type = MSG_PULL;
    send(fd,&msg,sizeof(msg),0);
    recv(fd, &msg, sizeof(msg), MSG_WAITALL);
    if(msg.type == MSG_END) return;
    String client_hash = msg.buf2;
    Vector<String> server_hashes = read_all_lines(HEAD.c_str());
    fileToMsg(HEAD,msg);
    msg.type = MSG_PULL;
    send(fd,&msg,sizeof(msg),0);
    fileToMsg(LOG,msg);
    send(fd,&msg,sizeof(msg),0);
    int i = 0;
    if(client_hash != ""){
        while(client_hash != server_hashes[i]){
            i++;
        }
        i++;
    }
    while(i<server_hashes.size()){
        String dir = COMMITS_DIR + "/" + deleteEndl(server_hashes[i]) + "/";
        Vector<String> files = ls(dir.c_str());
        for(int j = 0; j < files.size();j++){
            String file = dir + files[j];
            fileToMsg(file,msg);
            msg.type = MSG_PULL;
            send(fd,&msg,sizeof(msg),0);
        }
        i++;
    }
    msg.type = MSG_END;
    send(fd,&msg,sizeof(msg),0);
}

int server(int argc, char *argv[]){
    if(argc < 1){
        printf("Need port number\n");
        exit(EXIT_FAILURE);
    }
    server_port = atoi(argv[0]);
    signal(SIGINT,server_quit);
    atexit(server_stop);
    init_server_web();
    while(1){
        if(epoll_wait(epoll_fd, &event, 1,-1) == -1){
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        struct sockaddr in_addr;
        socklen_t in_len = sizeof(in_addr);
        int fd = accept(event.data.fd, &in_addr, &in_len);
        if (fd == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        Msg msg;
        recv(fd, &msg, sizeof(msg), MSG_WAITALL);
        if(msg.type == MSG_PULL){
            server_pull(fd, msg);
        }
        if(msg.type == MSG_PUSH){
            server_push(fd, msg);
        }
        close(fd);
    }
}
