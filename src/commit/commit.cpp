#include <sstream>
#include <sys/stat.h>
#include "commit.h"
#include "../util/status.h"
#include "../util/config.h"

int commit(int argc, char *argv[]){
    Vector<FileStatus> status = stageStatus();
    if(status.size()==0){
        printf("Nothing to commit\n");
        exit(EXIT_SUCCESS);
    }
    if(argc <1){
        printf("Need commit msg\n");
        exit(EXIT_FAILURE);
    }
    String msg = argv[0];
    String str = strStatus(status);
    GlobalConfig globalConfig = getGlobalConfig();
    String time = getTime();
    String old_hash = last_commit_hash();
    String seed = msg + str + globalConfig.name + globalConfig.email + time + old_hash;
    String new_hash = hash(seed);
    String destination_dir = COMMITS_DIR + "/" + new_hash;

    mkdir(destination_dir.c_str(),DEFAULT_PERM);
    destination_dir += "/FILES";
    mkdir(destination_dir.c_str(),DEFAULT_PERM);
    Vector<String> files = ls(STAGE_DIR.c_str());
    for(int i = 0; i < files.size();i++){
        String dest = destination_dir + "/" + files[i];
        String source = STAGE_DIR + "/" + files[i];
        copy(source.c_str(),dest.c_str());
    }
    FILE * file = fopen(HEAD.c_str(),"a");
    fprintf(file,"%s\n",new_hash.c_str());
    fclose(file);
    file = fopen(LOG.c_str(),"a");

    fprintf(file,"------------\n");
    fprintf(file,"Hash: %s\n",new_hash.c_str());
    fprintf(file,"Msg: %s\n",msg.c_str());
    fprintf(file,"Create by name:%s email:%s\n",globalConfig.name.c_str(),globalConfig.email.c_str());
    fprintf(file,"On:%s\n\n",time.c_str());
    fclose(file);

    return 0;
}
