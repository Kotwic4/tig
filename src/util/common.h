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

const String STAGE_DIR = MAIN_DIR + "/STAGE";
const String COMMITS_DIR = MAIN_DIR + "/COMMITS";

const mode_t DEFAULT_PERM = 0777;
enum StatusEnum { added, removed, modified, none};

String hash(String str);
String last_commit_hash();
String getTime();
String read_all_lines_one(const char * filename);
bool file_exists(const char * filename);
bool checkIfRepository();
Vector<String> read_all_lines(const char * filename);
void copy(const char *source,const char *dest);
String hashToDir(String hash_code);


#endif //TIG_COMMON_H
