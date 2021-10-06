#ifndef PACK_H
#define PACK_H

#include"FileHead.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//#include <error.h>
#include <string>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <time.h>
#include <sys/time.h>

#include "filesystem.h"
using namespace std;



void strmncpy(char *s, int m, int n, char *t);
void path (char FN[],char * root,char* tem_src,char* tmpDirName) ;

int  list_dir_name(char* dirname,string names[MAX_FILE_COUNT], int tabs);
void pack(char* src,char* dest);
void unpack(char* src,char* dest);
class MyCab
{

public:
    FileHead fh;
private:
    char ObjectFilePathName[MAX_PATH];
    void printCAB();
    void Create_Folders(const char* dir);

public:
    MyCab();
    void AddFile(char * FilePathName);
    void SetOutPutFile(char * OutFile);
    long GetFileSize(FILE *pf);
    void DoMakeCAB();
    void DoUnCAB(char *CabFilePathName,char *dest);

};


#endif // PACK_H
