#include <sstream>
#include "common.h"

std::hash<std::string> hasher;

std::string hash(std::string str){
    std::stringstream ss;
    ss << hasher(str);
    std::string sService = ss.str();
    return sService;
}
