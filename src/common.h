#ifndef TIG_COMMON_H
#define TIG_COMMON_H

#include <iostream>
#include <string>

const std::string DIR_NAME = "./.tig";
const std::string HEAD = DIR_NAME + "/HEAD";

std::string hash(std::string str);

#endif //TIG_COMMON_H
