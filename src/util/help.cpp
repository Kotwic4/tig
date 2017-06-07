#include "help.h"

const int command_number = 14;
const char* commands[] = {
        "add",
        "checkout",
        "clone",
        "commit",
        "config",
        "diff",
        "help",
        "init",
        "log",
        "pull",
        "push",
        "reset",
        "server",
        "status"};

int help(int argc, char *argv[]){
    printf("Usage: tig <command> [<args>]\n");
    printf("List of commands:\n");
    for(int i = 0; i < command_number; i++){
        printf("%s\n",commands[i]);
    }
    return 0;
}
