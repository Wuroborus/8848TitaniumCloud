#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <string.h>
//#include <filesystem>
#include <stdlib.h>
using namespace std;
#define OK 0
#define ERR -1
#define KEY 0xa9




int FileConvert(char szOldFile[],char szNewFile[]);
long GetFileSize(FILE *pf);
void pJ(char str[],char inFile[],char outFile[]);
int cF(char str[],char inFile[],char outFile[]);
bool code(char szOldFile[],char szNewFile[],char code[]);
bool decode(char szOldFile[],char szNewFile[],char code[]);

bool isCoded(char src[]);

#endif
