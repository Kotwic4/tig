#ifndef TIG_STATUS_H
#define TIG_STATUS_H

#include "common.h"
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
#include <sstream>
#include "diff.h"

struct FileStatus{
    String filename;
    StatusEnum status;
};

void status();
Vector<String> ls(const char * dir_name);
Vector<FileStatus> stageStatus();
Vector<FileStatus> workStatus();
Vector<FileStatus> diffStatus(String new_dir,String old_dir);
String strStatus(Vector<FileStatus> result);

#endif //TIG_STATUS_H
