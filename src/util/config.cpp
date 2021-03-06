#include "config.h"

const String GLOBAL_CONFIG = String(getenv("HOME")) + "/CONFIG.txt";

GlobalConfig getGlobalConfig(){
    GlobalConfig globalConfig;
    globalConfig.name = "";
    globalConfig.email = "";
    if(!file_exists(GLOBAL_CONFIG.c_str())){
        char name[100];
        char email[100];
        printf("No global config\n");
        printf("user.name = ");
        scanf("%s",name);
        printf("user.email = ");
        scanf("%s",email);
        if(creat(GLOBAL_CONFIG.c_str(),DEFAULT_PERM)==-1){
            perror("creat");
            exit(EXIT_FAILURE);
        }
        FILE* file = fopen(GLOBAL_CONFIG.c_str(), "wa");
        if(file == NULL){
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fprintf(file,"user.name = %s\n",name);
        fprintf(file,"user.email = %s\n",email);
        fclose(file);
        printf("Global config setted\n");
    }
    Vector<String> list = read_all_lines(GLOBAL_CONFIG.c_str());
    for(int i =0 ;i < list.size();i++){
        char type[100];
        char value[100];
        sscanf(list[i].c_str(), "%s = %s\n", type, value);
        if(strcmp(type,"user.name")==0){
            globalConfig.name = String(value);
        }
        else if(strcmp(type,"user.email")==0){
            globalConfig.email = String(value);
        }
    }
    return globalConfig;
}

void config(){
    GlobalConfig globalConfig = getGlobalConfig();
    printf("user.name = %s\n",globalConfig.name.c_str());
    printf("user.email = %s\n",globalConfig.email.c_str());
}
