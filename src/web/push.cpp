#include "push.h"
#include "../util/status.h"

void push(int argc, char *argv[]){
    if(argc < 2){
        printf("need 2 arguments");
    }
    int port = atoi(argv[0]);
    char *address = argv[1];
    int sock = client_start(port,address);
    Msg msg;
    fileToMsg(HEAD,msg);
    msg.type = MSG_PUSH;
    send(sock,&msg,sizeof(msg),0);
    recv(sock, &msg, sizeof(msg), MSG_WAITALL);
    if(msg.type != MSG_END){
        String server_hash = msg.buf2;
        Vector<String> client_hashes = read_all_lines(HEAD.c_str());
        fileToMsg(HEAD,msg);
        msg.type = MSG_PULL;
        send(sock,&msg,sizeof(msg),0);
        fileToMsg(LOG,msg);
        send(sock,&msg,sizeof(msg),0);
        int i = 0;
        if(server_hash != ""){
            while(server_hash != client_hashes[i]){
                i++;
            }
            i++;
        }
        while(i<client_hashes.size()){
            String dir = COMMITS_DIR + "/" + deleteEndl(client_hashes[i]) + "/";
            Vector<String> files = ls(dir.c_str());
            for(int j = 0; j < files.size();j++){
                String file = dir + files[j];
                fileToMsg(file,msg);
                msg.type = MSG_PULL;
                send(sock,&msg,sizeof(msg),0);
            }
            i++;
        }
    }
    else{
        printf("Repositories not compatible\n");
    }
    client_stop();
}
