#ifndef TIG_COMMON_H
#define TIG_COMMON_H

#include <iostream>
#include <string>
#include <vector>

const std::string MAIN_DIR = "./.tig";

const std::string HEAD = MAIN_DIR + "/HEAD.txt";
const std::string LOG = MAIN_DIR + "/LOG.txt";

const std::string LOCAL_CONFIG = MAIN_DIR + "/CONFIG.txt";


const std::string STAGE_DIR = MAIN_DIR + "/STAGE";
const std::string STAGE_FILES_DIR = STAGE_DIR + "/FILES";
const std::string STAGE_SUM = STAGE_DIR + "/SUM.txt";

const std::string COMMITS_DIR = MAIN_DIR + "/COMMITS";

const mode_t DEFAULT_PERM = 0777;

std::string hash(std::string str);
bool file_exists(const char * filename);

enum StatusEnum { added, removed, modified, none};

std::vector<std::string> read_all_lines(const char * filename);
void copy(const char *source,const char *dest);

std::string last_commit_hash();
bool checkIfRepository();
std::string getTime();

#endif //TIG_COMMON_H
