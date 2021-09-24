#ifndef FILE_TIME_H
#define FILE_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


class file_time
{
private:

public:
    file_time();
    void changefiletime(char*,char*);
};

#endif // FILE_TIME_H
