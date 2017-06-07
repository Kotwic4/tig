#ifndef TIG_CONFIG_H
#define TIG_CONFIG_H

#include "common.h"

struct GlobalConfig{
    String name;
    String email;
};

struct LocalConfig{
    String name;
    String email;
};

GlobalConfig getGlobalConfig();
LocalConfig getLocalConfig();

int config(int argc, char *argv[]);



#endif //TIG_CONFIG_H
