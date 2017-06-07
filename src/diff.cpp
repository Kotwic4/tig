#include "diff.h"

int diff(int argc, char *argv[]){
    if(argc < 2){
        printf("diff need 2 or more arguments\n");
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

std::vector<DiffLine> diff_files(std::string new_filename, std::string old_filename){
    std::vector<std::string> lines1 = read_all_lines(new_filename.c_str());
    std::vector<std::string> lines2 = read_all_lines(old_filename.c_str());
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