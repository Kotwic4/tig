#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
#include <sstream>
#include "status.h"
#include "diff.h"

Vector<String> ls(const char * dir_name){
    Vector<String> result;
    DIR *mydir = opendir(dir_name);
    if(mydir != NULL){
        char buf[512];
        struct dirent *myfile;
        struct stat sb;
        while((myfile = readdir(mydir)) != NULL){
            sprintf(buf, "%s/%s",".", myfile->d_name);
            stat(buf, &sb);
            if(S_ISREG(sb.st_mode)){
                String s = myfile->d_name;
                result.push_back(s);
            }
        }
    }
    return result;
}

FileStatus initFileStatus(String filename,StatusEnum status){
    FileStatus fileStatus;
    fileStatus.filename = filename;
    fileStatus.status = status;
    return fileStatus;
}

Vector<FileStatus> diffStatus(String new_dir,String old_dir){
    Vector<FileStatus> result;
    Vector<String> new_files = ls(new_dir.c_str());
    Vector<String> old_files = ls(old_dir.c_str());
    sort(new_files.begin(),new_files.end());
    sort(old_files.begin(),old_files.end());
    int i = 0;
    int j = 0;
    while(i < new_files.size() && j < old_files.size()){
        if(new_files[i] == old_files[j]){
            String file1 = new_dir + "/" + new_files[i];
            String file2 = old_dir + "/" + old_files[j];
            if(diff_files(file1,file2).size()>0){
                FileStatus fileStatus = initFileStatus(new_files[i],modified);
                result.push_back(fileStatus);
            }
            i++;
            j++;
        }
        else{
            if(new_files[i] > old_files[j]){
                FileStatus fileStatus = initFileStatus(old_files[j],removed);
                result.push_back(fileStatus);
                j++;
            }
            else{
                FileStatus fileStatus = initFileStatus(new_files[i],added);
                result.push_back(fileStatus);
                i++;
            }
        }
    }
    while(i < new_files.size()){
        FileStatus fileStatus = initFileStatus(new_files[i],added);
        result.push_back(fileStatus);
        i++;
    }
    while(j < old_files.size()){
        FileStatus fileStatus = initFileStatus(old_files[j],removed);
        result.push_back(fileStatus);
        j++;
    }
    return result;
}

Vector<FileStatus> workStatus(){
    String new_dir = ".";
    Vector<FileStatus> result = diffStatus(new_dir,STAGE_FILES_DIR);
    return result;
}

Vector<FileStatus> stageStatus(){
    String old_dir = COMMITS_DIR + "/" + last_commit_hash() + "/FILES";
    Vector<FileStatus> result = diffStatus(STAGE_FILES_DIR,old_dir);
    return result;
}

String strStatus(Vector<FileStatus> result){
    std::stringstream ss;
    for(int i = 0; i < result.size();i++){
        switch(result[i].status){
            case added:
                ss << "A ";
                break;
            case removed:
                ss << "R ";
                break;
            case modified:
                ss << "M ";
                break;
            case none:break;
        }
        ss << result[i].filename << Endl;
    }
    return ss.str();
}

int status(int argc, char *argv[]){
    Vector<FileStatus> result;
    printf("staged:\n");
    result = stageStatus();
    Cout << strStatus(result);
    result = workStatus();
    printf("\nnot staged:\n");
    Cout << strStatus(result);
    return 0;
}