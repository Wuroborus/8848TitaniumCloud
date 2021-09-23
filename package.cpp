#include<iostream>
#include <cstring>
using namespace std;
#include <fstream>
#include <string.h>
//索引表大小：n  文件数量：n   文件1大小 文件1偏移  文件1名大小 文件1名  文件2.。。
struct FileInfo
{
  int fileNameSize;  //文件名字大小
  int fileOffset;    //文件的偏移量
  int fileSize;    //文件的大小
  char fileName[20];  //文件名
};

int main()
{
    int n;
    cout<<"文件个数：";
    cin>>n;
    string s[n];
    FileInfo fileList[n];
    for(int i=0;i<n;i++)
    {   cout<<"输入路径：";
        cin>>s[i];
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
    fstream outfile("new.pack", ios_base::out | ios_base::binary);
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
    for (int i = 0; i < n; i++)
    {
        while (ch = file[i].get(),!file[i].eof())
        {
            outfile.put(ch);
        }
        file[i].close();
    }
    outfile.close();
}