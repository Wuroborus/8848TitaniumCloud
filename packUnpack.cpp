#include <fstream>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "packUnpack.h"
using namespace std;

/***** Global Variables *****/
char dir[100] = "/home";
int const MAX_STR_LEN = 200;

struct FileInfo
{
    int fileNameSize;  //文件名字大小
    int fileOffset;    //文件的偏移量
    int fileSize;    //文件的大小
    char fileName[200];  //文件名
};


void Opendir(const char* path, int *n, string *str)
{
    struct dirent* filename;
    DIR* dir = opendir(path);
    while((filename = readdir(dir))!= NULL)
    {
        // get rid of "." and ".."
        if( strcmp( filename->d_name , "." ) == 0 ||
            strcmp( filename->d_name , "..") == 0    )
            continue;
        (*n)++;
        // cout<<filename ->d_name <<endl;


        //*(str + (*n - 1))=filename->d_name;

        char* fileName;
        strcpy(fileName, path);
        strcat(fileName, "/");
        strcat(fileName, filename->d_name);
        *(str + (*n - 1)) = fileName;
        // store the relative path
        if(filename->d_type == 4)
        {
            // dir
            char* subpath;
            strcpy(subpath, path);
            strcat(subpath, "/");
            strcat(subpath, filename->d_name);
            Opendir(subpath, n, str);
        }
    }
}

/* Show all files under dir_name , do not show directories ! */
int showAllFiles( const char * dir_name,string *str )
{
    // check the parameter !
    if( dir_name == NULL )
    {
//        cout<<" dir_name is null ! "<<endl;
        return 0;
    }

    // check if dir_name is a valid dir
    struct stat s;
    lstat( dir_name , &s );
    if( ! S_ISDIR( s.st_mode ) )
    {
//        cout<<"dir_name is not a valid directory !"<<endl;
        return 0;
    }
   int n=0;
    /* read all the files in the dir ~ */
    Opendir(dir_name, &n, str);
    return n;
}



bool packUnpack::pack(const char *path,string s2)
{
    int n;
//    cout<<"文件个数：";
//    cin>>n;
    string s[100];
    n=showAllFiles(path,s);
    FileInfo fileList[n];
    for(int i=0;i<n;i++)
    {
//        cout<<"输入路径：";
//        cin>>s[i];
        fileList[i].fileNameSize=0;
        fileList[i].fileOffset=0;
        fileList[i].fileSize=0;
        strcpy(fileList[i].fileName,s[i].c_str());
    }



    fstream file[n];

    int listSize = 0;  //索引表大小
    int fileNum = n;  //文件数量
    for (int i = 0; i < n; i++)
    {
        fileList[i].fileNameSize = strlen(fileList[i].fileName) + 1;  //1是\0
        listSize += fileList[i].fileNameSize + 12;  //求索引表的大小

        file[i].open(fileList[i].fileName, ios_base::in | ios_base::binary);  //打开文件
        file[i].seekp(0, ios_base::end);          //读指针移动到末尾
        fileList[i].fileSize = file[i].tellp();        //获取文件大小
        file[i].seekp(0, ios_base::beg);          //读指针移动到开头
    }
    //写文件索引信息
    fstream outfile(s2, ios_base::out | ios_base::binary);
    outfile.write((char*)&listSize, n);
    outfile.write((char*)&fileNum, n);
    //写索引表
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            fileList[i].fileOffset = 8 + listSize;
        else
            fileList[i].fileOffset = fileList[i - 1].fileOffset + fileList[i - 1].fileSize;

        outfile.write((char*)&fileList[i].fileNameSize, n);
        outfile.write((char*)&fileList[i].fileOffset, n);
        outfile.write((char*)&fileList[i].fileSize, n);
        outfile.write((char*)&fileList[i].fileName, fileList[i].fileNameSize);
    }
    //写文件
    char ch;
    for (int i = 1; i < n; i++)
    {
        while ((ch = file[i].get()) != file[i].eof())
        {
            outfile.put(ch);
        }
        file[i].close();
    }
    outfile.close();
    return true;
}

bool packUnpack::unpack(const char *path)
{   fstream inFile;
    int n;
    string s[100];

    n=showAllFiles(path,s);
    inFile.open(path, ios_base::in | ios_base::binary);
    int listSize;  //索引表大小
    int fileNum;  //文件数量
    //读文件索引信息
    inFile.read((char*)&listSize, n);
    inFile.read((char*)&fileNum, n);

    FileInfo* fileList = new FileInfo[fileNum];
    fstream *file = new fstream[fileNum];
    //读索引表
    for (int i = 0; i < fileNum; i++)
    {
        inFile.read((char*)&fileList[i].fileNameSize, n);
        inFile.read((char*)&fileList[i].fileOffset, n);
        inFile.read((char*)&fileList[i].fileSize, n);
        inFile.read((char*)&fileList[i].fileName, fileList[i].fileNameSize);
        file[i].open(fileList[i].fileName, ios_base::out|ios_base::binary);
    }

    for (int i = 0; i < fileNum; i++)
    {
        for (int j = 0; j < fileList[i].fileSize; j++)
        {
            file[i].put(inFile.get());
        }
        file[i].close();
    }
    inFile.close();
    delete[] fileList;
    delete[] file;
}


