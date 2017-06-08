#ifndef TIG_DIFF_H
#define TIG_DIFF_H

#include <vector>
#include "common.h"
#include "status.h"

struct DiffLine{
    StatusEnum status_enum;
    int line_number;
    String line;
};

int diff(int argc, char *argv[]);

Vector<DiffLine> diff_files(String new_filename, String old_filename);

#endif //TIG_DIFF_H
