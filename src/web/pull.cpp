#include <sys/stat.h>
#include "pull.h"
#include "../util/status.h"

void pull(int argc, char *argv[]){
    if(argc < 2){
        printf("need 2 arguments\n");
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[0]);
    char *address = argv[1];
    int sock = client_start(port,address);
    Msg msg;
    msg.type = MSG_PULL;
    send(sock,&msg,sizeof(msg),0);
    recv(sock, &msg, sizeof(msg), MSG_WAITALL);
    Vector<String> server_hashes = msgToStrings(msg.buf2);
    Vector<String> client_hashes = read_all_lines(HEAD.c_str());
    int i = 0;
    int j = 0;
    while(i < server_hashes.size() && j < client_hashes.size()){
        if(server_hashes[i] == client_hashes[i]){
            i++;
            j++;
        }
        else{
            printf("Repositories not compatible\n");
            exit(EXIT_FAILURE);
        }
    }
    if(i < server_hashes.size()){
        if(i == 0){
            strcpy(msg.buf2,"");
        }
        else{
            strcpy(msg.buf2,server_hashes[i-1].c_str());
        }
        while(i < server_hashes.size()){
            String s = COMMITS_DIR + "/" +  deleteEndl(server_hashes[i]);
            mkdir(s.c_str(),DEFAULT_PERM);
            i++;
        }
        send(sock,&msg,sizeof(msg),0);
        if(recv(sock, &msg, sizeof(msg), MSG_WAITALL) == -1){
            perror("recv");
            exit(EXIT_FAILURE);
        }
        while(msg.type != MSG_END){
            printf("%s\n",msg.buf);
            FILE * file = fopen(msg.buf,"w");
            fprintf(file,"%s",msg.buf2);
            fclose(file);
            if(recv(sock, &msg, sizeof(msg), MSG_WAITALL) == -1){
                perror("recv");
                exit(EXIT_FAILURE);
            }
        }
        String dir = COMMITS_DIR + "/" + deleteEndl(last_commit_hash()) + "/";
        Cout << dir << Endl;
        Vector<String> files = ls(dir.c_str());
        Cout << files.size() << Endl;
        for(int k = 0; k < files.size();k++){
            String source = dir + files[k];
            Cout << source << Endl;
            String destination = STAGE_DIR + "/" + files[k];
            copy(source.c_str(),destination.c_str());
        }
    }
    client_stop();
}
