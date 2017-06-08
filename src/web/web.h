#ifndef TIG_WEB_H
#define TIG_WEB_H

#define _BSD_SOURCE
#define MSG_BUF 1000

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "../util/common.h"

enum MsgType {
    MSG_PULL,
    MSG_PUSH,
    MSG_END};

struct Msg{
    MsgType type;
    char buf[MSG_BUF];
    char buf2[MSG_BUF];
};

void fileToMsg(String filename, Msg &msg);
Vector<String> msgToStrings(char * msg_buf);

#endif //TIG_WEB_H
