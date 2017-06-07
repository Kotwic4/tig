#include <sstream>
#include <unistd.h>
#include "common.h"

std::hash<std::string> hasher;

std::string hash(std::string str){
    std::stringstream ss;
    ss << hasher(str);
    std::string sService = ss.str();
    return sService;
}

bool file_exists(const char * filename){
    return access(MAIN_DIR.c_str(), F_OK ) != -1;
}
