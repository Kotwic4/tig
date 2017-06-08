#include "diff.h"

DiffLine init_diff_line(StatusEnum status_enum,int line_number, String line){
    DiffLine diff_line;
    diff_line.status_enum = status_enum;
    diff_line.line_number = line_number;
    diff_line.line = line;
    return diff_line;
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

void printDiffLines(Vector<DiffLine> diff_lines){
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

int diff(int argc, char *argv[]){
    if(argc < 2){
        printf("diff need 2 or more arguments\n");
        exit(EXIT_FAILURE);
    }
    String new_dir = hashToDir(argv[0]);
    String old_dir = hashToDir(argv[1]);
    if (argc < 3){
        Vector<FileStatus> status = diffStatus(new_dir, old_dir);
        Cout << strStatus(status);
    } else{
        new_dir += "/";
        new_dir += argv[2];
        old_dir += "/";
        old_dir += argv[2];
        Vector<DiffLine> diff_lines = diff_files(new_dir,old_dir);
        printDiffLines(diff_lines);
    }
    return 0;
}
