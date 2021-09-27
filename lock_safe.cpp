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
    for(int i=0;i<32;i++){
        str[i]=str[i]^KEY;
    }
    char pd[32]={'s'};
    for(int i=0;i<32;i++){
        pd[i]=pd[i]^KEY;
    }


    FILE *pWorkFile1 = NULL;
    pWorkFile1 = fopen(inFile,"rb");
    long  len=GetFileSize(pWorkFile1);
    fclose(pWorkFile1);
    FILE *pOutFile = NULL;
    FILE *pWorkFile = NULL;
    pWorkFile = fopen(inFile,"rb");
    pOutFile = fopen(outFile,"wb");
    fwrite(str,32,1,pOutFile);
    fwrite(pd,32,1,pOutFile);

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
    char s1[32];
    FILE *pCAB = NULL;
    FILE *pWork = NULL;

    pCAB = fopen(inFile,"rb");
    fread(s,32,1,pCAB);
    fread(s1,32,1,pCAB);

    for(int i=0;i<32;i++){
        s[i]=s[i]^KEY;
    }
    unsigned char *pTmpData = NULL;
    pTmpData = new unsigned char[all-64];
    fread(pTmpData,all-64,1,pCAB);
    for(int i=0;i<strlen(str) ;i++){
        if(str[i]!=s[i] || s[i] == '\0'){
            printf("password error");
            return -1;
        }
    }
    pWork = fopen(outFile,"wb");
    fwrite(pTmpData,all-64,1,pWork);
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
bool isCoded(char src[]){

    FILE *pCAB = NULL;
    pCAB = fopen(src,"rb");
    char pd[32]={'s'};
    for(int i=0;i<32;i++){
        pd[i]=pd[i]^KEY;
    }
    char pd1[32];
    char pd2[32];


    fread(pd1,32,1,pCAB);
    fread(pd2,32,1,pCAB);

    for(int i=0;i<32;i++){
        if(pd2[i]!=pd[i]){
            printf("fei jia mi------------");
            return false;
        }

    }
    printf("jia mi-------------");

    return true;


}







//int main(int argc, char* argv[]) {
//    char s1[200];
//    char s2[200];
//    char s_code[32];
//    cout<<"文件1：";
//    cin>>s1;
//    cout<<"文件2：";
//    cin>>s2;
//    cout<<"password:";
//    cin>>s_code;
//    int n;
//    cout<<"1：加密  2：解密  ";
//    cin>>n;
//    if(n==1){
//        code(s1, s2, s_code);//source dest code
//    }

//    else{
//         decode(s1, s2, s_code);//source dest code
//    }





//    return 0;
//}






