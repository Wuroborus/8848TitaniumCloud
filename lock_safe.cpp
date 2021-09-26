#include "lock_safe.h"

int FileConvert(char szOldFile[],char szNewFile[])
{
    FILE *pOldFile=NULL;
    FILE *pNewFile=NULL;//指针初始化为NULL
    char cTemp;

    if(szOldFile==NULL||szNewFile==NULL)
    {
        return ERR;
    }

    pOldFile=fopen(szOldFile,"rb");//二进制读写文件
    if(pOldFile==NULL)
    {
        return ERR;
    }

    pNewFile=fopen(szNewFile,"wb");
    if(pNewFile==NULL)
    {
        fclose(pOldFile);
        return ERR;
    }
    //一定要先读取字符然后做文件末尾判断
    cTemp=fgetc(pOldFile);
    while(!feof(pOldFile))//遇到文件结束 返回值为0
    {
//        putchar(cTemp);
        fputc(cTemp,pNewFile);
        cTemp=fgetc(pOldFile)^KEY;//异或运算加密文件

    }
    fclose(pOldFile);
    fclose(pNewFile);//用完文件之后需要关闭文件

    return OK;
}

long GetFileSize(FILE *pf)
{
    //指针移到文件尾
    fseek(pf,0,/*SEEK_END*/ 2);
    return ftell(pf);
}

//ping jie
void pJ(char str[],char inFile[],char outFile[]){
    FILE *pWorkFile1 = NULL;
    pWorkFile1 = fopen(inFile,"rb");
    long  len=GetFileSize(pWorkFile1);
    fclose(pWorkFile1);
    FILE *pOutFile = NULL;
    FILE *pWorkFile = NULL;
    pWorkFile = fopen(inFile,"rb");
    pOutFile = fopen(outFile,"wb");
    fwrite(str,32,1,pOutFile);
    unsigned char *pTmpData = NULL;
    pTmpData = new unsigned char[len];
    fread(pTmpData,len,1,pWorkFile);
    fwrite(pTmpData,len,1,pOutFile);

    fclose(pWorkFile);
    fclose(pOutFile);
}


//chai fen
int cF(char str[],char inFile[],char outFile[]){
    FILE *pCAB1 = NULL;
    pCAB1 = fopen(inFile,"rb");
    long all=GetFileSize(pCAB1);
    fclose(pCAB1);
    char s[32];//mi ma
    FILE *pCAB = NULL;
    FILE *pWork = NULL;

    pCAB = fopen(inFile,"rb");
    fread(s,32,1,pCAB);
    unsigned char *pTmpData = NULL;
    pTmpData = new unsigned char[all-32];
    fread(pTmpData,all-32,1,pCAB);
    for(int i=0;i<32;i++){
        if(str[i]!=s[i]){
            printf("password error");
            return -1;
        }
    }
    pWork = fopen(outFile,"wb");
    fwrite(pTmpData,all-32,1,pWork);
    fclose(pWork);
    fclose(pCAB);
    return 0;
}

 int code(char szOldFile[],char szNewFile[],char code[]){

    char* s1=szOldFile;
    char s2[strlen(s1)+1];
    for(int i=0;i<strlen(s1);i++){
        s2[i]=s1[i];
    }
    s2[strlen(s1)]='1';
    FileConvert( szOldFile, s2);
    pJ(code,s2,szNewFile);
    remove(s2);

    return 0;
}



int decode(char szOldFile[],char szNewFile[],char code[]){
    printf("++++++++++++++++++++++++++");//bu neng shan
    char s2[strlen(szOldFile)+1];
    for(int i=0;i<strlen(szOldFile);i++){
        s2[i]=szOldFile[i];
    }
    s2[strlen(szOldFile)]='1';
    if( cF(code,szOldFile,s2)<0) return -1;;
    FileConvert( s2, szNewFile);
    remove(s2);

    return 0;
}








