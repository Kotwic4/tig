#include "push.h"

void push(int argc, char *argv[]){
    if(argc < 2){
        printf("need 2 arguments");
    }
    int port = atoi(argv[0]);
    char *address = argv[1];
    client_start(port,address);

    //todo

    client_stop();
}
