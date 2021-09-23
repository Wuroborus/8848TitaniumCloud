#ifndef FILE_TIME_H
#define FILE_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct file_stats
{
    struct stat* f_stat;
    file_stats* next;
};



class file_time
{
private:
    file_stats* first;
    file_stats* tail;
public:
    file_time();
    void gotfiletime(char*);
    void changefiletime(char*,file_stats*);
    file_stats* getfile_stats();
};

#endif // FILE_TIME_H
