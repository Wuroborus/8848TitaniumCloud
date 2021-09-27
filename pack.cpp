#include "pack.h"



void strmncpy(char *s, int m, int n, char *t)
{

    char *p=s,*q=t;
    p+=m;
    while(*p!='\0'&&n){
        *q=*p;
        p++;
        q++;
        n--;
    }
    *q='\0';
}


void path (char FN[],char * root,char* tem_src,char* tmpDirName) {
    char fn [MAX_PATH];
    strcpy(fn,root);

    char *tmp1 = fn + strlen(fn);
    while( '/' != *tmp1)
    {
        tmp1--;
    }
    memset(tmpDirName,0x0,sizeof(tmpDirName));
    strcpy(tmpDirName,tmp1);
    char fileName[MAX_PATH];
    char *tmp3 = FN + strlen(FN);
    while( '/' != *tmp3)
    {
        tmp3--;
    }
    memset(fileName,0x0,sizeof(fileName));
    strcpy(fileName,tmp3);
    char* tmp2=FN + strlen(fn);
    strcat(tmpDirName,tmp2);
    char *s = tmpDirName;

    strmncpy(s,0,strlen(tmpDirName)-strlen(fileName),tem_src);


}

int  list_dir_name(char* dirname,string names[MAX_FILE_COUNT], int tabs=0)
{
    DIR* dp;
    struct dirent* dirp;
    struct stat st;
    char tab[tabs + 1];
    if((dp = opendir(dirname)) == NULL)
    {
        perror("opendir");
        return -1;
    }

    memset(tab, '\t', tabs);
    tab[tabs] = 0;
    while((dirp = readdir(dp)) != NULL)
    {
        char fullname[MAX_PATH];
        memset(fullname, 0, sizeof(fullname));
        if(dirp->d_name[0] == '.')
            continue;

        strncpy(fullname, dirname, sizeof(fullname));
        strncat(fullname, "/", sizeof(fullname));
        strncat(fullname, dirp->d_name, sizeof(fullname));
        if(stat(fullname, &st) == -1)
        {
            perror("stat");
            fputs(fullname, stderr);
            return -1;
        }
        if(S_ISREG(st.st_mode)){  //copy full_name
            for(int i=0;i<MAX_FILE_COUNT;i++)
            {
                if(names[0]==""){
                    names[0]=fullname;
                    break;
                }
                if(names[i]!=""&&names[i+1]==""){
                    names[i+1]=fullname;
                    break;
                }

                if(names[i]==""&&names[i+1]==""){
                    break;
                }
            }

        }
        if(S_ISDIR(st.st_mode) && list_dir_name(fullname, names,tabs + 1) == -1)
            return -1;
    }
    return 0;
}


MyCab::MyCab()
{
    memset(&fh,0x0,sizeof(fh));
    memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
}


//添加文件到包内
void  MyCab:: AddFile(char * FilePathName)
{
    if ( fh.FileCount >= MAX_FILE_COUNT - 1 )
    {
        cout<<"最多支持"<<MAX_FILE_COUNT<<"个文件"<<endl;
        return;
    }
    strcpy(fh.FileName[fh.FileCount],FilePathName);
    fh.FileCount++;
}

//设置打包输出文件
void  MyCab::SetOutPutFile(char * OutFile)
{
    memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
    strcpy(ObjectFilePathName,OutFile);
}

//获取文件大小(传入以二进制方式打开的文件指针)
long MyCab:: GetFileSize(FILE *pf)
{
    //指针移到文件尾
    fseek(pf,0,/*SEEK_END*/ 2);
    return ftell(pf);
}

//制作打包文件
void MyCab:: DoMakeCAB()
{
    if ( fh.FileCount < 1 )
    {
        cout<<"没有文件添加到打包"<<endl;
        return;
    }
    if ( strlen(ObjectFilePathName) < 1 )
    {
        cout<<"没有指定打包文件输出位置"<<endl;
        return;
    }

    FILE *pOutFile = NULL;
    FILE *pWorkFile = NULL;

    //获取所有文件大小
    for ( int i = 0 ; i < fh.FileCount ; i++ )
    {
        pWorkFile = fopen(fh.FileName[i],"rb");
        if ( NULL == pWorkFile )
        {
            cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
            return;
        }
        fh.FileLen[i] = GetFileSize(pWorkFile);
        fclose(pWorkFile);
    }

    //开始合并写文件
    pOutFile = fopen(ObjectFilePathName,"wb");
    if ( NULL == pOutFile )
    {
        cout<<"输出文件创建失败["<<strerror(errno)<<"]"<<endl;
        return;
    }

    //写入文件头
    fwrite(&fh,sizeof(fh),1,pOutFile);
    //写入各文件
    for ( int i = 0 ; i < fh.FileCount ; i++ )
    {
        unsigned char *pTmpData = NULL;
        pWorkFile = fopen(fh.FileName[i],"rb");
        if ( NULL == pWorkFile )
        {
            cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
            fclose(pWorkFile);
            fclose(pOutFile);
            return;
        }
        pTmpData = new unsigned char[fh.FileLen[i]];
        fread(pTmpData,fh.FileLen[i],1,pWorkFile);
        if ( ferror(pWorkFile) )
        {
            cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
            fclose(pWorkFile);
            fclose(pOutFile);
            return;
        }
        fwrite(pTmpData,fh.FileLen[i],1,pOutFile);
        if ( ferror(pOutFile) )
        {
            cout<<"文件:"<<ObjectFilePathName<<"无法写入["<<strerror(errno)<<"]"<<endl;
            fclose(pWorkFile);
            fclose(pOutFile);
            return;
        }
        delete [] pTmpData;
        fclose(pWorkFile);
    }

    fclose(pOutFile);
    cout<<"打包完成"<<endl;
}

//解包
void  MyCab::DoUnCAB(char *CabFilePathName,char *dest)
{
    FILE *pCAB = NULL;
    FILE *pWork = NULL;
    pCAB = fopen(CabFilePathName,"rb");
    //读文件头

    memset(&fh,0x0,sizeof(fh));
    fread(&fh,sizeof(fh),1,pCAB);


    printCAB();
    //解包单文件


    bool fl=false;
    for(int i=0;i<MAX_PATH;i++){
        if(fh.src[i]!=0){
            fl=true;
        }
    }



    if(!fl){

        unsigned char *pTmpData = NULL;
        pTmpData = new unsigned char[fh.FileLen[0]];
        fread(pTmpData,fh.FileLen[0],1,pCAB);
        //只取文件名,不要生成文件的路径名
        char tmpFileName[MAX_PATH];
        char *ptmpC = fh.FileName[0] + strlen(fh.FileName[0]);
        while( '/' != *ptmpC)
        {
            ptmpC--;
        }
        *ptmpC = '\0';

        memset(tmpFileName,0x0,sizeof(tmpFileName));
        strcpy(tmpFileName,dest);//加上目的路径
        strcat(tmpFileName,ptmpC);
        pWork = fopen(tmpFileName,"wb");
        fwrite(pTmpData,fh.FileLen[0],1,pWork);
        fclose(pWork);
        delete [] pTmpData;
        fclose(pCAB);
    }

    else{
        for ( int i = 0 ; i < fh.FileCount ; i++ )
        {


            char tmpDirName[MAX_PATH];
            char tem_src[MAX_PATH];
            path (fh.FileName[i], fh.src,tem_src,tmpDirName);//获取相对路径




            unsigned char *pTmpData = NULL;
            pTmpData = new unsigned char[fh.FileLen[i]];
            fread(pTmpData,fh.FileLen[i],1,pCAB);
            //只取文件名,不要生成文件的路径名
            char tmpFileName[MAX_PATH];
            char *ptmpC = fh.FileName[i] + strlen(fh.FileName[i]);
            while( '/' != *ptmpC)
            {
                ptmpC--;
            }
            memset(tmpFileName,0x0,sizeof(tmpFileName));
            strcpy(tmpFileName,ptmpC+1);




            //取CAB文件路径
            char tmpPathName[MAX_PATH];
            memset(tmpPathName,0x0,sizeof(tmpPathName));

            strcpy(tmpPathName,CabFilePathName);
            ptmpC = tmpPathName + strlen(tmpPathName);
            while('/' != *ptmpC)
            {
                ptmpC--;
            }

            *ptmpC = '\0';

            char filPath[MAX_PATH];
            memset(filPath,0x0,sizeof(filPath));
            strcat(filPath,dest);
            strcat(filPath,tmpDirName);


            char filDir[MAX_PATH];
            memset(filDir,0x0,sizeof(filDir));



            strcat(filDir,dest);

            strcat(filDir,tem_src);


            Create_Folders(filDir);

            strcat(tmpPathName,tmpFileName);
            pWork = fopen(filPath,"wb");




            fwrite(pTmpData,fh.FileLen[i],1,pWork);

            fclose(pWork);
            delete [] pTmpData;
        }

        fclose(pCAB);


    }
}


//显示打包内文件信息
void  MyCab:: printCAB()
{
    cout<<"文件内信息如下:"<<endl;
    cout<<"文件总数:"<<fh.FileCount<<endl;
    for ( int i = 0 ; i < fh.FileCount ; i++ )
    {
        cout<<fh.FileName[i]<<"\t\t\t\t"<<fh.FileLen[i]<<"字节"<<endl;
    }
}

void MyCab:: Create_Folders(const char* dir){
    char order[100] = "mkdir -p ";
    strcat(order, dir);
    system(order);
}

void pack(char* src,char* dest){
    //声明对象
    MyCab mc;
    //设置输出文件
    mc.SetOutPutFile(dest);

    struct stat state_of_entry;
    lstat(src, &state_of_entry);
    if (S_ISDIR(state_of_entry.st_mode)) //如果要复制的是文件夹
    {
//            mc.fh.src=src;
        strcpy(mc.fh.src,src);



        string names[MAX_FILE_COUNT];
        list_dir_name(src,names);
        for(int i=0;i<MAX_FILE_COUNT;i++)
        {
            if(names[i]!=""){
                //添加要打包的文件
                mc.AddFile((char*)names[i].c_str());//(char*)str.c_str()

            }
            if(names[i]==""&&names[i+1]==""){
                mc.DoMakeCAB();


                break;
            }
        }


    }

    else{
        for(int i=0;i<MAX_PATH;i++){
            mc.fh.src[i]=0;
        }

        //添加要打包的文件
        mc.AddFile(src);
        mc.DoMakeCAB();

    }
}

void unpack(char* src,char* dest){

    MyCab umc;
    //执行解包

    umc.DoUnCAB(src,dest);


}



