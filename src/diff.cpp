#include "diff.h"

int diff(int argc, char *argv[]){
    if(argc < 2){
        printf("diff need 2 or more arguments");
    }
    else{
        std::vector<DiffLine> diff_lines = diff_files(argv[0],argv[1]);
        for(int i = 0; i < diff_lines.size(); i++){
            switch(diff_lines[i].status_enum){
                case added:
                    std::cout << "A ";
                    break;
                case removed:
                    std::cout << "R ";
                    break;
                case modified:break;
                case none:break;
            }
            std::cout << diff_lines[i].line_number << " " << diff_lines[i].line;
        }
    }
    return 0;
}

std::vector<std::string> read_all_lines(FILE* file){
    size_t line_size=0;
    char* line_buf=0;
    std::vector<std::string> lines;
    while (getline(&line_buf, &line_size, file)>0) {
        std::string line = line_buf;
        lines.push_back(line);
    }
    free(line_buf);
    line_buf=NULL;
    return lines;
}

std::vector<DiffLine> diff_files(std::string new_filename, std::string old_filename){
    FILE* file1 = fopen(new_filename.c_str(), "r");
    FILE* file2 = fopen(old_filename.c_str(), "r");
    std::vector<std::string> lines1 = read_all_lines(file1);
    std::vector<std::string> lines2 = read_all_lines(file2);
    std::vector<DiffLine> result;
    int i = 0;
    int j = 0;
    while(i < lines1.size() and j < lines2.size()){
        if(lines1[i] == lines2[j]){
            i++;
            j++;
        }
        else{
            int k = j+1;
            for(; k < lines2.size();k++){
                if(lines1[i] == lines2[k]){
                    break;
                }
            }
            if (k == lines2.size()){
                result.push_back(init_diff_line(added,i,lines1[i]));
                i++;
            }
            else{
                while(j < k){
                    result.push_back(init_diff_line(removed,j,lines2[j]));
                    j++;
                }
            }
        }
    }
    while(i < lines1.size()){
        result.push_back(init_diff_line(added,i,lines1[i]));
        i++;
    }
    while(j < lines2.size()){
        result.push_back(init_diff_line(removed,j,lines2[j]));
        j++;
    }
    return result;
}

DiffLine init_diff_line(StatusEnum status_enum,int line_number, std::string line){
    DiffLine diff_line;
    diff_line.status_enum = status_enum;
    diff_line.line_number = line_number;
    diff_line.line = line;
    return diff_line;
}