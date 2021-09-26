
#include"pack_unpack.h"
#include <iostream>
using namespace std;
int main()
{
    char fdname[50];
    char fname[50];
    cout<<"文件夹：";
    cin>>fdname;
    cout<<"dir:";
    cin>>fname;
    int n;
    cout<<"选择 1：打包 2：解包"；

    cin>>n;
    if(n==1){
        pack(fdname,fname);

    }
    else{

    unpack(fdname,fname);
    }



}
