#include<iostream>
using namespace std;
#include <fstream>
struct FileInfo
{
    int fileNameSize;  //文件名字大小
    int fileOffset;    //文件的偏移量
    int fileSize;    //文件的大小
    char fileName[20];  //文件名
};
int main()
{   int n;
    cout<<"文件数：";
cin>>n;
    char s;
    cout<<"文件名：";
    cin>>s;
    fstream inFile;
    inFile.open(reinterpret_cast<const char *>(s), ios_base::in | ios_base::binary);
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