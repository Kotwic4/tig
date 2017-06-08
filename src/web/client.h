#ifndef TIG_CLIENT_H
#define TIG_CLIENT_H

#include "../util/common.h"
#include "web.h"

int client_start(int port, char* address);
void client_stop();

#endif //TIG_CLIENT_H
