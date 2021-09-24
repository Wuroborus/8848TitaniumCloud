#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include <cassert>
#include <list>

using namespace std;

void encfile(char *in_filename,char *pwd);
void decryptfile(char* in_filename,char *pwd);
void getFileContent(string str);

string content;
string *content_array = new string[2048];

struct generateInfo {
    string password;
    string checked;
    string username;
    string company;
};

int main(int argc,char *argv[]) {
    char in_filename[30] = "test.txt";
    char pwd[8] = "config";
    encfile(in_filename,pwd);
    decryptfile(in_filename,pwd);
    generateInfo info;
    info.checked = content_array[4];
    info.password = content_array[2];
    info.username = content_array[6];
    info.company = content_array[8];

    cout<< info.username <<endl;
    cout<< info.password <<endl;
    cout<< info.company <<endl;
    cout<< info.checked <<endl;

    return 0;
}

/*加密函数*/
void encfile(char *in_filename,char *pwd) {
    FILE *fp1;
    register char ch;
    int j=0;
    int j0=0;
    string temp;
    fp1=fopen(in_filename,"r");/*打开要加密的文件*/
    if(fp1==NULL) {
        printf("cannot open in-file./n");
        exit(1);/*如果不能打开要加密的文件,便退出程序*/
    }
    while(pwd[++j0]);

    ch=fgetc(fp1);

    /*加密算法开始*/
    while(!feof(fp1)) {
        if(j0 >7)
            j0 = 0;
        ch += pwd[j0++];
        temp += ch;
        ch=fgetc(fp1);

    }
    fclose(fp1);
    ofstream out(in_filename);
    out<<temp<<endl;
    out.close();
}

/*解密函数*/
void decryptfile(char *in_filename,char *pwd) {
    FILE *fp1;
    register char ch;
    int j=0;
    int j0=0;
    string temp;
    fp1=fopen(in_filename,"r");/*打开要解密的文件*/
    if(fp1==NULL) {
        printf("cannot open in-file./n");
        exit(1);
    }

    while(pwd[++j0]);
    ch=fgetc(fp1);

    while(!feof(fp1)) {
        if(j0 >7)
            j0 = 0;
        ch -= pwd[j0++];
        temp += ch;
        ch=fgetc(fp1);
    }
    fclose(fp1);/*关闭源文件*/
    getFileContent(temp.data());
}

//获取解密后文件的内容
void getFileContent(string str) {

    const char *d = " =\r\n";   //根据空格、等于号、回车、换行截取字符串
    char s[2048];
    strcpy(s,str.c_str());  //将字符串转成char[]
    char *p;
    p = strtok(s,d);
    int i = 1;  //数组下标变量

    list<string> info_list;
    list<string>::iterator itor;

    while(p) {
        info_list.push_back(p);  //将元素放在list的最后面
        p=strtok(NULL,d);
    }
    itor = info_list.begin();  //循环迭代
    while(itor!=info_list.end()) {
        content_array[i] = *itor;
        *itor++;
        i++;
    }

}





