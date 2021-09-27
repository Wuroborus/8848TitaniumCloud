
#include "filesystem.h"

void OpenThedir(const char *path, int *n, string *str)
{
    struct dirent* filename;
    DIR* dir = opendir(path);
    while((filename = readdir(dir))!= NULL)
    {
        // get rid of "." and ".."
        if( strcmp( filename->d_name , "." ) == 0 ||
            strcmp( filename->d_name , "..") == 0    )
            continue;
        // store the relative path
        if(filename->d_type == 4)
        {
            // dir
            char* subpath = new char[200];
            strcpy(subpath, path);
            strcat(subpath, "/");
            strcat(subpath, filename->d_name);
            OpenThedir(subpath, n, str);
        }
        else {
            (*n)++;
            char* fileName = new char[200];
            strcpy(fileName, path);
            strcat(fileName, "/");
            strcat(fileName, filename->d_name);
            str[*n - 1] = fileName;
        }
    }
}

void fileSystem::getAllFiles(const char *path, int *n, string *str)
{
    *n = 0;
    OpenThedir(path, n, str);
}
