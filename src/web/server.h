#ifndef TIG_SERVER_H
#define TIG_SERVER_H

#include "../util/common.h"
#include "web.h"

#include <sys/epoll.h>
#define N 100

int server(int argc, char *argv[]);

#endif //TIG_SERVER_H
