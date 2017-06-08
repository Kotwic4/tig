#include "checkout.h"

void checkout(int argc, char *argv[]){
    if(argc < 1){
        printf("add need 1 or more arguments\n");
    }
    else{
        String destination = argv[0];
        String source = STAGE_DIR + "/" + destination;
        destination = "./" + destination;
        if(file_exists(source.c_str())){
            if(!file_exists(destination.c_str())){
                if(creat(destination.c_str(),DEFAULT_PERM)==-1){
                    perror("creat");
                    exit(EXIT_FAILURE);
                }
            }
            Vector<DiffLine> result = diff_files(source,destination);
            if(result.size()>0){
                copy(source.c_str(),destination.c_str());
            }
            else{
                printf("Nothing to checkout\n");
            }
        }
        else{
            if(file_exists(destination.c_str())){
                unlink(destination.c_str());
            }
            else{
                printf("Nothing to checkout\n");
            }
        }
    }
}
