#include <fcntl.h>
#include "add.h"
#include "diff.h"

int add(int argc, char *argv[]){
    if(argc < 1){
        printf("add need 1 or more arguments\n");
    }
    else{
        String source = argv[0];
        String destination = STAGE_FILES_DIR + "/" + source;
        if(!file_exists(destination.c_str())){
            if(creat(destination.c_str(),DEFAULT_PERM)==-1){
                perror("creat");
                exit(EXIT_FAILURE);
            }
        }
        Vector<DiffLine> result = diff_files(source,destination);
        if(result.size()>0){
            printf("Added %s\n",source.c_str());
            source = "./" + source;
            copy(source.c_str(),destination.c_str());
        }
        else{
            printf("Nothing to add\n");
        }
    }
    return 0;
}


