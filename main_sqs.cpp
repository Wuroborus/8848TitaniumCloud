

#include"pack.h"


int main(int argc, char *argv[]){

    char s1[200];
    cout<<"文件路径：";
    cin>>s1;
    char s2[200];
    cout<<"目标路径：";
    cin>>s2;
    int n;
    cout<<"选择 1：打包  2：解包   ";
    cin>>n;
    if(n==1){
        pack(s1,s2);
    }
    else{
        unpack(s1,s2);
    }


    return 0;

}






