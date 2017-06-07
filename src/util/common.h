#ifndef TIG_COMMON_H
#define TIG_COMMON_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <unistd.h>
#include <vector>

#define String std::string
#define Vector std::vector
#define Cout std::cout
#define Cin std::cin
#define Endl std::endl

const String MAIN_DIR = "./.tig";

const String HEAD = MAIN_DIR + "/HEAD.txt";
const String LOG = MAIN_DIR + "/LOG.txt";

const String LOCAL_CONFIG = MAIN_DIR + "/CONFIG.txt";


const String STAGE_DIR = MAIN_DIR + "/STAGE";
const String STAGE_FILES_DIR = STAGE_DIR + "/FILES";
const String STAGE_SUM = STAGE_DIR + "/SUM.txt";

const String COMMITS_DIR = MAIN_DIR + "/COMMITS";

const mode_t DEFAULT_PERM = 0777;
enum StatusEnum { added, removed, modified, none};



String hash(String str);
bool file_exists(const char * filename);
Vector<String> read_all_lines(const char * filename);
void copy(const char *source,const char *dest);
String last_commit_hash();
bool checkIfRepository();
String getTime();

#endif //TIG_COMMON_H
