#include "web.h"

void fileToMsg(String filename, Msg &msg){
    sprintf(msg.buf,"%s",filename.c_str());
    String s = read_all_lines_one(filename.c_str());
    sprintf(msg.buf2,"%s",s.c_str());
}

Vector<String> msgToStrings(char * msg_buf){
    Vector<String> result;
    char* buf = strtok(msg_buf, "\n");
    while(buf){
        String s = buf;
        s += "\n";
        result.push_back(s);
        buf = strtok(NULL, "\n");
    }
    return result;
}