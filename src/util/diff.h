#ifndef TIG_DIFF_H
#define TIG_DIFF_H

#include <vector>
#include "common.h"

struct DiffLine{
    StatusEnum status_enum;
    int line_number;
    String line;
};

int diff(int argc, char *argv[]);

Vector<String> read_all_lines(FILE* file);

Vector<DiffLine> diff_files(String new_filename, String old_filename);

DiffLine init_diff_line(StatusEnum status_enum,int line_number, String line);



#endif //TIG_DIFF_H
