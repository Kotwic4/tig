#include "common.h"

std::hash<String> hasher;

String hash(String str){
    std::stringstream ss;
    ss << hasher(str);
    String sService = ss.str();
    return sService;
}

bool file_exists(const char * filename){
    return access(filename, F_OK ) != -1;
}

Vector<String> read_all_lines(const char * filename){
    FILE* file = fopen(filename, "r");
    size_t line_size=0;
    char* line_buf=0;
    Vector<String> lines;
    while (getline(&line_buf, &line_size, file)>0) {
        String line = line_buf;
        lines.push_back(line);
    }
    free(line_buf);
    line_buf=NULL;
    return lines;
}

String read_all_lines_one(const char * filename){
    Vector<String> lines = read_all_lines(filename);
    String result = "";
    for(int i = 0; i < lines.size();i++){
        result += lines[i];
    }
    return result;
}

void copy(const char *source, const char *dest) {
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

String last_commit_hash(){
    Vector<String> commits = read_all_lines(HEAD.c_str());
    if (commits.size() == 0){
        return "";
    }
    else{
        String s = commits[commits.size()-1];
        if (!s.empty() && s[s.length()-1] == '\n') {
            s.erase(s.length()-1);
        }
        return s;
    }
}

bool checkIfRepository(){
    return file_exists(MAIN_DIR.c_str());
}

String getTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
    return String(buffer);
}

String hashToDir(String hash_code){
    if(hash_code == "Stage"){
        return STAGE_DIR;
    }
    if(hash_code == "Work"){
        return ".";
    }
    return COMMITS_DIR + "/" + hash_code;
}
