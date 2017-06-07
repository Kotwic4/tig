#ifndef TIG_CONFIG_H
#define TIG_CONFIG_H

#include "common.h"

struct GlobalConfig{
    std::string name;
    std::string email;
};

struct LocalConfig{
    std::string name;
    std::string email;
};

GlobalConfig getGlobalConfig();
LocalConfig getLocalConfig();

int config(int argc, char *argv[]);



#endif //TIG_CONFIG_H
