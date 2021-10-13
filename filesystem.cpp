
#include "filesystem.h"

bool openDir(string path, vector<string>& fileList) {
    struct dirent* file;
    DIR* dir = opendir(path.c_str());
    while ((file = readdir(dir)) != NULL) {
        // get rid of "." and ".."
        if( strcmp( file->d_name , "." ) == 0 ||
            strcmp( file->d_name , "..") == 0    )
            continue;
        string newpath = path + "/" + file->d_name;
        if(file->d_type == 4) {
            openDir(newpath.c_str(), fileList);
        }
        else {
            fileList.push_back(newpath);
        }
    }
    return true;
}

fileSystem::fileSystem(const char *path)
{
    openDir(path, this->fileList);
    fileTypeList.resize(fileList.size());
    inodeList.resize(fileList.size());
    linkList.resize(fileList.size());
}

bool fileSystem::getFileType()
{
    struct stat buf;
    for(int i = 0; i < fileList.size(); i++) {
        lstat(fileList[i].c_str(), &buf);
        if(S_ISLNK(buf.st_mode)) {
            char* oldpath = new char[300];
            int result = readlink(fileList[i].c_str(), oldpath, MAX_PATH);
            if(result <0 || result >= MAX_PATH) return false;
            else {
                oldpath[result] ='\0';
                if(oldpath[0] == '/' || oldpath[0] == '.') {
                    fileTypeList[i] = SYM_OUT;
                }
                else {
                    fileTypeList[i] = SYM_IN;
                }
            }
        }
        else if (buf.st_nlink != 1) {
            fileTypeList[i] = HARD_IN;
        }
        else {
            fileTypeList[i] = REG_FILE;
        }
        inodeList[i] = buf.st_ino;
        linkList[i] = buf.st_nlink;
    }
    return true;
}

bool fileSystem::getFileList(const char* path)
{
    fileList.clear();
    openDir(path, this->fileList);
    return true;
}

