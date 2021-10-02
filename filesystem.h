#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

// file type
#define REG_FILE 0
#define SYM_IN 1
#define SYM_OUT 2
#define HARD_IN 3
#define HARD_OUT 4

#define MAX_PATH 300

using namespace std;

class fileSystem{
public:
    int count;
    vector<string>fileList;
    vector<int>fileTypeList;
    vector<size_t>inodeList;
    vector<nlink_t>linkList;


public:
    fileSystem(const char* path);
    bool getFileType();
};

#endif // FILESYSTEM_H
