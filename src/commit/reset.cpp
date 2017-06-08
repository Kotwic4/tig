#include "reset.h"

void reset(int argc, char *argv[]){
    if(argc < 1){
        printf("add need 1 or more arguments\n");
    }
    else{
        String source = argv[0];
        String destination = STAGE_DIR + "/" + source;
        source = hashToDir(last_commit_hash()) + "/" + source;
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
                printf("Nothing to reset\n");
            }
        }
        else{
            if(file_exists(destination.c_str())){
                unlink(destination.c_str());
            }
            else{
                printf("Nothing to reset\n");
            }
        }
    }
}

