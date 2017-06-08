#include "init.h"

void init(){

    if( !checkIfRepository() ) {
        if(mkdir(MAIN_DIR.c_str(),DEFAULT_PERM)==-1){
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
        if(mkdir(STAGE_DIR.c_str(),DEFAULT_PERM)==-1){
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
        if(mkdir(COMMITS_DIR.c_str(),DEFAULT_PERM)==-1){
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
        if(creat(HEAD.c_str(),DEFAULT_PERM)==-1){
            perror("creat");
            exit(EXIT_FAILURE);
        }
        if(creat(LOG.c_str(),DEFAULT_PERM)==-1){
            perror("creat");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("tig repository already initialized\n");
    }
}
