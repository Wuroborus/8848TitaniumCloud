#include "file_increment.h"
#include<iostream>
#include<sys/types.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

file_increment::file_increment()
{

}

int file_increment::IncrementBackUp(char *pathfrom, char *pathto)
{
    char* named = new char[50];
    char* tonamed = new char[50];
    for(int i = 0;i<=99;i++)
    {
        memset(named,0,50);
        strcpy(named,pathto);
        strcat(named,"/8848back_up_");
        strcat(named,std::to_string(i).c_str());
        if(opendir(named))
        {
            continue;
        }
        else {
            memset(named,0,50);
            strcpy(named,pathto);
            strcat(named,"/8848back_up_");
            strcat(named,std::to_string(i-1).c_str());
            strcpy(tonamed,named);
            strcat(tonamed,"_increment");
            break;
        }
    }
    char* order = new char[100];

    strcpy(order,"mkdir -p ");
    strcat(order,tonamed);
    system(order);

    DIR *dirfrom, *dirto;
    struct dirent *ptrfrom,*ptrto;
    struct stat s_from,s_to;
    char* filename = new char[100];

    char basef[500],baset[500];
//    char* changeorder = new char[1000];
    if ((dirfrom=opendir(pathfrom)) == NULL || (dirto = opendir(pathto)) == NULL)
    {
       perror("Open dir error...");
       return -1;
    }
    while (1)
    {
        //(ptr=readdir(dir)) != NULL
        if((ptrfrom = readdir(dirfrom)) == NULL || (ptrto = readdir(dirto)) == NULL)
        {
            if((ptrfrom = readdir(dirfrom)) != NULL || (ptrto = readdir(dirto)) != NULL)
            {
                perror("files not match or can't read dir...");
                return -1;
            }
            break;
        }
       if(strcmp(ptrfrom->d_name,".")==0 || strcmp(ptrfrom->d_name,"..")==0)    ///current dir OR parrent dir
          continue;
       stat(ptrfrom->d_name,s_from);
       stat(ptrto->d_name,s_to);
       if(s_from.st_mtime != s_to.st_mtime)
       {
           memset(basef,'\0',sizeof(basef));
           strcpy(basef,pathfrom);
           strcat(basef,"/");
           strcat(basef,ptrfrom->d_name);
           memset(baset,'\0',sizeof(baset));
           strcpy(baset,pathfrom);
           strcat(baset,"/");
           strcat(baset,ptrto->d_name);
           memset(order,0,100);
           strcpy(order,"cp -a ");
           strcat(order,basef);
           strcat(order," ");
           strcat(order,baset);
           system(order);
       }


//       memset(changeorder,0,100);
//       strcpy(changeorder,"touch -r ");
//       char* f_time = new char[20];

//       strcat(changeorder,pathfrom);
//       strcat(changeorder,"/");
//       strcat(changeorder,ptrfrom->d_name);
//       strcat(changeorder," ");
//       strcat(changeorder,pathto);
//       strcat(changeorder,"/");
//       strcat(changeorder,ptrto->d_name);
//       system(changeorder);
       //next = next->next;
       if(ptrfrom->d_type == 4){
           memset(basef,'\0',sizeof(basef));
           strcpy(basef,pathfrom);
           strcat(basef,"/");
           strcat(basef,ptrfrom->d_name);
           memset(baset,'\0',sizeof(baset));
           strcpy(baset,pathfrom);
           strcat(baset,"/");
           strcat(baset,ptrto->d_name);
           IncrementBackUp(basef,baset);
        }
    }
    closedir(dirfrom);
    closedir(dirto);
}
