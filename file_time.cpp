#include "file_time.h"
#include <time.h>
#include<stdlib.h>

file_time::file_time()
{

}

void file_time::changefiletime(char *basePathFrom, char *basePathTo)
{
    DIR *dirfrom, *dirto;
    struct dirent *ptrfrom,*ptrto;
    char* filename = new char[100];

    char basef[500],baset[500];
    char* changeorder = new char[1000];
    if ((dirfrom=opendir(basePathFrom)) == NULL || (dirto = opendir(basePathTo)) == NULL)
    {
       perror("Open dir error...");
       return;
    }
    while (1)
    {
        //(ptr=readdir(dir)) != NULL
        if((ptrfrom = readdir(dirfrom)) == NULL || (ptrto = readdir(dirto)) == NULL)
        {
            if((ptrfrom = readdir(dirfrom)) != NULL || (ptrto = readdir(dirto)) != NULL)
            {
                perror("files not match or can't read dir...");
                return;
            }
            break;
        }
       if(strcmp(ptrfrom->d_name,".")==0 || strcmp(ptrfrom->d_name,"..")==0)    ///current dir OR parrent dir
          continue;

       memset(changeorder,0,100);
       strcpy(changeorder,"touch -r ");
       char* f_time = new char[20];
//       ltoa(next->f_stat->st_atime,f_time,20);
//       strcat(changeorder,f_time);
//       strcat(changeorder," ");
       strcat(changeorder,basePathFrom);
       strcat(changeorder,"/");
       strcat(changeorder,ptrfrom->d_name);
       strcat(changeorder," ");
       strcat(changeorder,basePathTo);
       strcat(changeorder,"/");
       strcat(changeorder,ptrto->d_name);
       system(changeorder);
       //next = next->next;
       if(ptrfrom->d_type == 4){
           memset(basef,'\0',sizeof(basef));
           strcpy(basef,basePathFrom);
           strcat(basef,"/");
           strcat(basef,ptrfrom->d_name);
           memset(baset,'\0',sizeof(baset));
           strcpy(baset,basePathFrom);
           strcat(baset,"/");
           strcat(baset,ptrto->d_name);
           changefiletime(basef,baset);
        }
    }
    closedir(dirfrom);
    closedir(dirto);
    return ;
}

//在需改时间处添加代码：
//    file_time* GotFromtime = new file_time;
//    char* cpathfrom;
//    char* cpathto;
//    strcpy(cpathfrom,constcpathfrom);
//    strcpy(cpathto,constcpathto);
//    GotFromtime->changefiletime(cpathfrom,cpathto);

