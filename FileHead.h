#ifndef FILEHEAD_H
#define FILEHEAD_H

#define MAX_FILE_COUNT  1024
//最大路径字符长度
#define MAX_PATH   300
//文件头
struct FileHead
{
    unsigned int FileCount;//文件个数
    unsigned int FileLen[MAX_FILE_COUNT];//文件大小
    char FileName[MAX_FILE_COUNT][MAX_PATH];//文件名
    char src[MAX_PATH];//待打包 的文件夹路径
};


#endif // FILEHEAD_H
