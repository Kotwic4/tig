#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
#include <sstream>
#include "status.h"
#include "diff.h"

std::vector<std::string> ls(const char * dir_name){
    std::vector<std::string> result;
    DIR *mydir = opendir(dir_name);
    if(mydir != NULL){
        char buf[512];
        struct dirent *myfile;
        struct stat sb;
        while((myfile = readdir(mydir)) != NULL){
            sprintf(buf, "%s/%s",".", myfile->d_name);
            stat(buf, &sb);
            if(S_ISREG(sb.st_mode)){
                std::string s = myfile->d_name;
                result.push_back(s);
            }
        }
    }
    return result;
}

FileStatus initFileStatus(std::string filename,StatusEnum status){
    FileStatus fileStatus;
    fileStatus.filename = filename;
    fileStatus.status = status;
    return fileStatus;
}

std::vector<FileStatus> diffStatus(std::string new_dir,std::string old_dir){
    std::vector<FileStatus> result;
    std::vector<std::string> new_files = ls(new_dir.c_str());
    std::vector<std::string> old_files = ls(old_dir.c_str());
    sort(new_files.begin(),new_files.end());
    sort(old_files.begin(),old_files.end());
    int i = 0;
    int j = 0;
    while(i < new_files.size() && j < old_files.size()){
        if(new_files[i] == old_files[j]){
            std::string file1 = new_dir + "/" + new_files[i];
            std::string file2 = old_dir + "/" + old_files[j];
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

std::vector<FileStatus> workStatus(){
    std::string new_dir = ".";
    std::vector<FileStatus> result = diffStatus(new_dir,STAGE_FILES_DIR);
    return result;
}

std::vector<FileStatus> stageStatus(){
    std::string old_dir = COMMITS_DIR + "/" + last_commit_hash() + "/FILES";
    std::vector<FileStatus> result = diffStatus(STAGE_FILES_DIR,old_dir);
    return result;
}

std::string strStatus(std::vector<FileStatus> result){
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
        ss << result[i].filename << std::endl;
    }
    return ss.str();
}

int status(int argc, char *argv[]){
    std::vector<FileStatus> result;
    printf("staged:\n");
    result = stageStatus();
    std::cout << strStatus(result);
    result = workStatus();
    printf("\nnot staged:\n");
    std::cout << strStatus(result);
    return 0;
}