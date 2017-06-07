#ifndef TIG_CONFIG_H
#define TIG_CONFIG_H

#include "common.h"

int config(int argc, char *argv[]);

struct UserConfig{
    std::string name;
    std::string email;
};

struct Config{
    struct UserConfig userConfig;
};

#endif //TIG_CONFIG_H
