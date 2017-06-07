#ifndef TIG_DIFF_H
#define TIG_DIFF_H

#include <vector>
#include "common.h"

struct DiffLine{
    StatusEnum status_enum;
    int line_number;
    std::string line;
};

int diff(int argc, char *argv[]);

std::vector<std::string> read_all_lines(FILE* file);

std::vector<DiffLine> diff_files(std::string new_filename, std::string old_filename);

DiffLine init_diff_line(StatusEnum status_enum,int line_number, std::string line);



#endif //TIG_DIFF_H
