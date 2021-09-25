#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <dirent.h>
#include <string.h>

using namespace std;

class fileSystem{
private:

public:
    void getAllFiles(const char* path, int *n, string *str);

};

#endif // FILESYSTEM_H
