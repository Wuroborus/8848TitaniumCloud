#include "file_time.h"

file_time::file_time()
{

}

void file_time::gotfiletime(char * basePath)
{
    if(first == NULL)
    {
        first = new file_stats;
        tail = first;
    }
    else
    {
    DIR *dir;
    struct dirent *ptr;
    char* filename = new char[100];
    struct file_stats* next = new file_stats;
    char base[1000];
    if ((dir=opendir(basePath)) == NULL)
    {
       //perror("Open dir error...");
       return;
    }
    while ((ptr=readdir(dir)) != NULL)
    {
       if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
          continue;
       strcpy(filename,basePath);
       strcat(filename,"/");
       strcat(filename,ptr->d_name);
       stat(filename,next->f_stat);
       tail->next = next;
       tail = next;
       tail->next = NULL;
       if(ptr->d_type == 4){
           memset(base,'\0',sizeof(base));
           strcpy(base,basePath);
           strcat(base,"/");
           strcat(base,ptr->d_name);
           gotfiletime(base);
        }
    }
    closedir(dir);
    return ;
    }
}

file_stats* file_time::getfile_stats()
{
    return first;
}

void file_time::changefiletime(char *basePath, file_stats *LinkHeadFrom)
{
    DIR *dir;
    struct dirent *ptr;
    char* filename = new char[100];
    struct file_stats* next = LinkHeadFrom->next;

    char base[1000];
    char* changeorder = new char[100];
    if ((dir=opendir(basePath)) == NULL)
    {
        //perror("  ");
       return ;
    }
    while ((ptr=readdir(dir)) != NULL)
    {
       if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
          continue;

       memset(changeorder,0,100);
       strcpy(changeorder,"touch -a -t ");
       char* f_time = new char[20];
       sprintf(f_time,"%l",next->f_stat->st_atime);
       strcat(changeorder,f_time);
       strcat(changeorder," ");
       strcat(changeorder,basePath);
       strcat(changeorder,"/");
       strcat(changeorder,ptr->d_name);
       system(changeorder);
       //if(next->next != NULL)
          next = next->next;
       if(ptr->d_type == 4){
           memset(base,'\0',sizeof(base));
           strcpy(base,basePath);
           strcat(base,"/");
           strcat(base,ptr->d_name);
           changefiletime(base,next);
        }
    }
    closedir(dir);
    return ;
}
