#include "init.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

int init(int argc, char *argv[]){
    if( access(DIR_NAME.c_str(), F_OK ) == -1 ) {
        if(mkdir(DIR_NAME.c_str(),0777)==-1){
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
