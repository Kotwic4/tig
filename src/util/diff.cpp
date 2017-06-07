#include "diff.h"

int diff(int argc, char *argv[]){
    if(argc < 2){
        printf("diff need 2 or more arguments\n");
    }
    else{
        Vector<DiffLine> diff_lines = diff_files(argv[0],argv[1]);
        for(int i = 0; i < diff_lines.size(); i++){
            switch(diff_lines[i].status_enum){
                case added:
                    Cout << "A ";
                    break;
                case removed:
                    Cout << "R ";
                    break;
                case modified:break;
                case none:break;
            }
            Cout << diff_lines[i].line_number << " " << diff_lines[i].line;
        }
    }
    return 0;
}

Vector<DiffLine> diff_files(String new_filename, String old_filename){
    Vector<String> lines1 = read_all_lines(new_filename.c_str());
    Vector<String> lines2 = read_all_lines(old_filename.c_str());
    Vector<DiffLine> result;
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

DiffLine init_diff_line(StatusEnum status_enum,int line_number, String line){
    DiffLine diff_line;
    diff_line.status_enum = status_enum;
    diff_line.line_number = line_number;
    diff_line.line = line;
    return diff_line;
}