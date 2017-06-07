#ifndef TIG_STATUS_H
#define TIG_STATUS_H

#include "common.h"

struct FileStatus{
    std::string filename;
    StatusEnum status;
};

int status(int argc, char *argv[]);
std::vector<std::string> ls(const char * dir_name);\
std::vector<FileStatus> stageStatus();
std::vector<FileStatus> workStatus();
std::vector<FileStatus> diffStatus(std::string new_dir,std::string old_dir);
std::string strStatus(std::vector<FileStatus> result);

#endif //TIG_STATUS_H
