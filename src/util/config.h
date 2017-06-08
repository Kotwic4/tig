#ifndef TIG_CONFIG_H
#define TIG_CONFIG_H

#include "common.h"
#include <fcntl.h>
#include <cstring>

struct GlobalConfig{
    String name;
    String email;
};

GlobalConfig getGlobalConfig();

void config();

#endif //TIG_CONFIG_H
