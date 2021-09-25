#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
#include "lock_unlock.h"
using namespace std;

//const char* s = "csjknahdhkadlbk";
bool lock_unlock::lock(char* s,char *buffer)
{

    FILE* fp_src1, * fp_src2;

    int i, j, l, k = 0;
    long int size;

    fp_src1=fopen(s, "rb+");
    if (fp_src1 == NULL) {
        perror("open1");
        exit(0);
    }

    fseek(fp_src1, 0, SEEK_SET);
    fseek(fp_src1, 0, SEEK_END);
    size = ftell(fp_src1);
    fseek(fp_src1, 0, SEEK_SET);
    char* buffer1 = new char[size];
    char* buffer2 = new char[size];
//    string s1=buffer2;
    string s2 =buffer;
    strcpy(buffer2,s2.c_str());



//    cin >> buffer2;
//    buffer2 = (char*)s;
    do {
        i = fread(buffer1, 1, size, fp_src1);
        if (feof(fp_src1)) break;
        for (i = 0; i < size; i++)
            buffer1[i] = buffer1[i] ^ buffer2[i];  //"^" 为异或 ，异或实现加密操作
        k++;
    } while (!feof(fp_src1));
    fclose(fp_src1);
    fp_src1=fopen(s, "wb");
    if (fp_src1 == NULL) {
        perror("open5");
        exit(0);
    }
    j = fwrite(buffer1, 1, size, fp_src1);
    //关闭文件
    fclose(fp_src1);
    return true;
}

bool lock_unlock::unlock(char* s,char *buffer)
{

    FILE* fp_src1, * fp_src2;

    int i, j, l, k = 0;
    long int size;

    fp_src1=fopen(s, "rb+");
    if (fp_src1 == NULL) {
        perror("open1");
        exit(0);
    }

    fseek(fp_src1, 0, SEEK_SET);
    fseek(fp_src1, 0, SEEK_END);
    size = ftell(fp_src1);
    fseek(fp_src1, 0, SEEK_SET);
    char* buffer1 = new char[size];
    char* buffer2 = new char[size];
//    string s1=buffer2;
    string s2 =buffer;
    strcpy(buffer2,s2.c_str());



//    cin >> buffer2;
//    buffer2 = (char*)s;
    do {
        i = fread(buffer1, 1, size, fp_src1);
        if (feof(fp_src1)) break;
        for (i = 0; i < size; i++)
            buffer1[i] = buffer1[i] ^ buffer2[i];  //"^" 为异或 ，异或实现加密操作
        k++;
    } while (!feof(fp_src1));
    fclose(fp_src1);
    fp_src1=fopen(s, "wb");
    if (fp_src1 == NULL) {
        perror("open5");
        exit(0);
    }
    j = fwrite(buffer1, 1, size, fp_src1);
    //关闭文件
    fclose(fp_src1);
    return true;
}