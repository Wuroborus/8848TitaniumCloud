#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>

using namespace std;
//char * creat_txt(){
//    char *str=;
//
//    return str;
//}
char *s="csjknahdhkadlbk";
int main()
    {

        FILE *fp_src1,*fp_src2;//两个文件指针,  FILE大写表示系统已经定义FILE这个变量
        //char buffer[],buffer1[120];
        int i, j, l, k = 0;
        long int size;
        FILE *fp  = fopen("key.txt", "w"); //这一行代表创建txt文件

        fprintf(fp,s);
        //打开文件“原文件.txt”，需要加（解）密的文件，r表示读，b表示以二进制方式读，
        if ((fp_src1 = fopen("test.txt", "rb+")) == NULL) {
            perror("open1");
            exit(0);
        }
        //打开文件“key.txt”，密钥文件，r表示读，b表示已二进制方式读，
        if ((fp_src2 = fopen("key.txt", "rb+")) == NULL) {
            perror("open2");
            exit(0);
        }

        fseek(fp_src1, 0, SEEK_SET);
        fseek(fp_src1, 0, SEEK_END);// 为了知道文件的大小
        size = ftell(fp_src1);//ftell（）的返回值为文件的大小
        fseek(fp_src1, 0, SEEK_SET);
        char buffer1[size], buffer2[size];
        do {
            i = fread(buffer1, 1, size, fp_src1);
            i = fread(buffer2, 1, size, fp_src2); //一个一个读文件，然后放入缓冲区
            if (feof(fp_src1)) break;
            // 1.feof（）这个函数是用来判断指针是否已经到达文件尾部的
            //2.若fp已经指向文件末尾，则feof（fp）函数值为“真”，即返回非零值；否则...
            for (i = 0; i < size; i++)
                buffer1[i] = buffer1[i] ^ buffer2[i];  //"^" 为异或 ，异或实现加密操作
            k++;
            //将缓冲区的内容写入目标区
        } while (!feof(fp_src1));
        //打开文件“原文件.txt”，需要加（解）密的文件，w表示读，b表示已二进制方式写
        if ((fp_src1 = fopen("test.txt", "wb+")) == NULL) {
            perror("open5");
            exit(0);
        }
        j = fwrite(buffer1, 1, size, fp_src1);
        //关闭文件
        fclose(fp_src1);
        fclose(fp_src2);
    }

//int main()
//{
//    FILE *fp_src1,*fp_src2;//两个文件指针,  FILE大写表示系统已经定义FILE这个变量
//    //char buffer[],buffer1[120];
//    int i,j,l,k=0;
//    long int size;
//    //打开文件“原文件.txt”，需要加（解）密的文件，r表示读，b表示以二进制方式读，
//    if((fp_src1=fopen("test.txt","rb+"))==NULL)
//    {
//        perror("open1");
//        exit(0);
//    }
//    //打开文件“key.txt”，密钥文件，r表示读，b表示已二进制方式读，
//    if((fp_src2=fopen("key.txt","rb+"))==NULL)
//    {
//        perror("open2");
//        exit(0);
//    }
//    fseek(fp_src1,0,SEEK_SET);
//    fseek(fp_src1,0,SEEK_END);// 为了知道文件的大小
//    size=ftell(fp_src1);//ftell（）的返回值为文件的大小
//    fseek(fp_src1,0,SEEK_SET);
//    char buffer1[size],buffer2[size];
//    do
//    {
//        i=fread(buffer1,1,size,fp_src1);
//        i=fread(buffer2,1,size,fp_src2); //一个一个读文件，然后放入缓冲区
//        if (feof(fp_src1)) break;
//        // 1.feof（）这个函数是用来判断指针是否已经到达文件尾部的
//        //2.若fp已经指向文件末尾，则feof（fp）函数值为“真”，即返回非零值；否则...
//        for (i=0; i<size; i++)
//            buffer1[i]=buffer1[i]^buffer2[i];  //"^" 为异或 ，异或实现加密操作
//        k++;
//        //将缓冲区的内容写入目标区
//    } while(!feof(fp_src1));
//    //打开文件“原文件.txt”，需要加（解）密的文件，w表示读，b表示已二进制方式写
//    if((fp_src1=fopen("test.txt","wb+"))==NULL)
//    {
//        perror("open5");
//        exit(0);
//    }
//    j=fwrite(buffer1,1,size,fp_src1);
//    //关闭文件
//    fclose(fp_src1);
//    fclose(fp_src2);
//}
