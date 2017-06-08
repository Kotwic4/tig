#include "client.h"

int sock = -1;

void init_client_web(int port, char*address){
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1){
        perror("Socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in web_addr;
    web_addr.sin_family = AF_INET;
    web_addr.sin_port = htons((uint16_t) port);

    if (inet_aton(address, &web_addr.sin_addr) == 0) {
        perror("inet_aton");
        exit(EXIT_FAILURE);
    }

    if(connect(sock,(struct sockaddr *)&web_addr,sizeof(web_addr)) == -1){
        perror("connect");
        exit(EXIT_FAILURE);
    }
}

void client_stop(){
    if(sock != -1){
        struct Msg msg;
        msg.type = MSG_END;
        send(sock,&msg,sizeof(msg),0);
        shutdown(sock,SHUT_RDWR);
        close(sock);
        sock = -1;
    }
}

void client_quit(int sig){
    exit(EXIT_SUCCESS);
}

int client_start(int port, char*address){
    signal(SIGINT,client_quit);
    atexit(client_stop);
    init_client_web(port,address);
    return sock;
}
