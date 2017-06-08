#include "server.h"
#include "../util/status.h"

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
    while(msg.type != MSG_END){
        recv(fd, &msg, sizeof(msg), MSG_WAITALL);
        printf("%s\n",msg.buf);
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
