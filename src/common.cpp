#include <sstream>
#include <unistd.h>
#include <vector>
#include <wait.h>
#include "common.h"
#include <ctime>

std::hash<std::string> hasher;

std::string hash(std::string str){
    std::stringstream ss;
    ss << hasher(str);
    std::string sService = ss.str();
    return sService;
}

bool file_exists(const char * filename){
    return access(filename, F_OK ) != -1;
}

std::vector<std::string> read_all_lines(const char * filename){
    FILE* file = fopen(filename, "r");
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

void copy(const char *source, const char *dest)
{
    FILE* file1 = fopen(source, "r");
    if(file1 == NULL){
        perror("file1");
        exit(EXIT_FAILURE);
    }
    FILE* file2 = fopen(dest, "wa");
    if(file2 == NULL){
        perror("file2");
        exit(EXIT_FAILURE);
    }
    size_t line_size=0;
    char* line_buf=0;
    while (getline(&line_buf, &line_size, file1) > 0) {
        fprintf(file2,"%s",line_buf);
    }
    free(line_buf);
    line_buf=NULL;
}

std::string last_commit_hash(){
    std::vector<std::string> commits = read_all_lines(HEAD.c_str());
    if (commits.size() == 0){
        return "";
    }
    else{
        std::string s = commits[commits.size()-1];
        if (!s.empty() && s[s.length()-1] == '\n') {
            s.erase(s.length()-1);
        }
        return s;
    }
}

bool checkIfRepository(){
    return file_exists(MAIN_DIR.c_str());
}

std::string getTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
    return std::string(buffer);
}