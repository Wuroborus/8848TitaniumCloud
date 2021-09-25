#include"huffman.h"
#include <iostream>
#include <string.h>
#include <bitset> //输出二进制的头文件
#include<limits>
#include<string>
using namespace std;

//全局变量，重构Huffman树时需要
int strIndex = 0;
int nodeIndex = 0;
int leafArrIndex = 0;
int length = 0;    //非重复字节个数;
unsigned char Ochar;
int Ocharlength = 0;
/*Huffman结点*/


void NodeList::insertlist(const unsigned char& Data) //尾插入；
{
    Node* p, * s;
    s = new(Node); //动态分配一个新结点
    s->Data = Data;
    s->weight = 1;
    p = head;
    if (head == NULL) //若是空表，创建第一个结点
    {
        head = s;
        s->next = NULL;
    }
    else
    {
        while (p->next != NULL) p = p->next;
        p->next = s;
        s->next = NULL;
    }
    len++;
}
void NodeList::run(const char* inFilename)
{
    FILE* fo = fopen( inFilename, "rb");                        //读入待压缩文件  读取二进制文件
    if (fo == NULL) {
        cerr << " Can not open！" << endl;
        exit(1);
    }
    unsigned char ch = fgetc(fo);                           //读取一个字符
    int pos;

    while (!feof(fo)) {                                              // 从文件当中读入字符 直到文件结束，并且统计字符个数
        pos = findPosition(ch);
        if (pos == -1)  insertlist(ch);                                             //新插入一个
        ch = fgetc(fo);
    }
    fclose(fo);
}
int NodeList::findPosition(const unsigned char& ch) const {
    Node* p;
    p = head;
    if (p == NULL) //若是空表
        return -1;
    while (p->Data!=ch )
    {
        if (p->next == NULL) return -1;  //表已遍历完
        else p = p->next;
    }
    p->weight += 1;
    return 0;
}
int NodeList::size() {
    return len;
}
int NodeList::getOcharlength(unsigned char& Ochar){
    Node* p;
    p = head;
    if (p == NULL) //若是空表
        return -1;
    while (p->Data != Ochar)
    {
        if (p->next == NULL) return -1;  //表已遍历完
        else p = p->next;
    }
    return p->weight;
}


//获得最左叶子结点信息
unsigned char HuffmanTree::getOchar(const int num) {
    if (arrayTree[num].lchild == -1) {          // 根据其为满二叉树的特性只判断左子树即可
        return arrayTree[num].it; //叶结点对应字节
    }
    getOchar(arrayTree[num].lchild);
}

/*run函数的实现*/
void HuffmanTree::run(NodeList list) {
    Node* p;
    p = list.gethead();
    for (int i = 0; i < len; i++) {
        if (p != NULL) {
            arrayTree[i].it = p->Data;
            arrayTree[i].weight = p->weight;
            p = p->next;
        }
        else cout << "出错";
    }
    buildHuffmanTree();                   //构造huffman树
    createHuffmanCode();               //对统计字符进行编码
}


/*压缩用  构造huffmanTree*/
void HuffmanTree::buildHuffmanTree() {
    int i = len;
    int k;
    double wt1, wt2;
    int lnode = 0, rnode = 0;
    while (i < 2 * len - 1) {
        wt1 = wt2 = numeric_limits<double>::max();   //返回编译器允许的 double 型数的最大值
        k = 0;
        while (k < i) {
            if (arrayTree[k].parent == -1) {
                if (arrayTree[k].weight < wt1) {
                    wt2 = wt1;
                    rnode = lnode;
                    wt1 = arrayTree[k].weight;                      //将 wt1 置为最小权重
                    lnode = k;
                }
                else if (arrayTree[k].weight < wt2) {
                    wt2 = arrayTree[k].weight;                      //将 wt2 置为第二小的
                    rnode = k;
                }
            }
            k++;
        }
        arrayTree[i].weight = arrayTree[lnode].weight + arrayTree[rnode].weight;
        arrayTree[i].lchild = lnode;
        arrayTree[i].rchild = rnode;
        arrayTree[lnode].parent = arrayTree[rnode].parent = i;
        i++;
    }
}

/*得到每种叶子结点的具体编码*/
void HuffmanTree::createHuffmanCode() {
    char *tempCodeArray=new char[len];                        //存放临时编码（初始倒序的编码）
    codeArray = new Code[2 * len - 1];   //存放所有字符的编码
    int i = 0;
    int Len = len * 2 - 1;                           //全部结点个数
    int k, n, m, t;
    while (i < Len) {
        k = arrayTree[i].parent;
        n = 0;
        m = i;
        while (k != -1 && k < Len) {
            if (arrayTree[k].lchild == m)
                tempCodeArray[n++] = '0';         //为左子树时添加 0
            else if (arrayTree[k].rchild == m)
                tempCodeArray[n++] = '1';         //为右子树时添加 1

            m = k;
            k = arrayTree[m].parent;
        }
        for (t = 0; t < n; t++) {                        //使 codeArray 存放正确顺序的编码
            codeArray[i].ptr[t] = tempCodeArray[n - 1 - t];
        }
        codeArray[i].ptr[n] = '\0';
        i++;
    }
    delete[] tempCodeArray;
    Ochar=getOchar(len * 2 - 2);
}
/*压缩用 将哈夫曼树写入文件*/
void HuffmanTree::writeCodeToFile(const char* outFilename) {
    FILE* fw;
    fw=fopen( outFilename, "wb");
    if (fw == NULL) {
        cout << "3文件打开失败!" << endl;
        return;
    }
    fprintf(fw, "%d ", Ocharlength);                   //写入源文件后缀名
    writeTreeStructureToFile(len * 2 - 2, fw); //从根结点写起，根结点保存在arrayTree最后
    fprintf(fw, " ");
    writeLeafToFile(len * 2 - 2, fw);               //从根结点起遍历，写入叶节点字符ASCII码
    fclose(fw);
}

/*压缩用  将哈夫曼树结构写入文件*/
void HuffmanTree::writeTreeStructureToFile(const int& num, FILE* fw) {
    if (arrayTree[num].lchild == -1) {
        fprintf(fw, "0");                         //根据树的顺序表示法 叶节点为0
        return;
    }
    else
    {
        fprintf(fw, "1");                         // 内部子节点为1
    }
    writeTreeStructureToFile(arrayTree[num].lchild, fw);
    writeTreeStructureToFile(arrayTree[num].rchild, fw);
}

/*压缩用 将叶节点信息写入文件*/
void HuffmanTree::writeLeafToFile(const int& num, FILE* fw) {
    if (arrayTree[num].lchild == -1) {          // 根据其为满二叉树的特性只判断左子树即可
        fprintf(fw, "%d ", arrayTree[num].it); //叶结点对应字母的ASCII码
        return;
    }
    writeLeafToFile(arrayTree[num].lchild, fw);
    writeLeafToFile(arrayTree[num].rchild, fw);
}

/*由信息构建Huffman树 解压时需要*/
void HuffmanTree::reBuildHuffmanTree(const unsigned char* str, const int* arr, int i) {
    if (str[strIndex] != '\0') {
        if (str[strIndex] == '1') {                                           //判断它是子节点
            strIndex++;
            int m = nodeIndex;
            int n = nodeIndex + 1;
            arrayTree[i].lchild = m;                                       //定义其左节点
            arrayTree[i].rchild = n;                                        //定义其右节点
            arrayTree[m].parent = arrayTree[n].parent = i;  //左右节点的根节点
            nodeIndex += 2;
            arrayTree[i].it = NULL;                                        //将父节点的信息设为空

            reBuildHuffmanTree(str, arr, m);
            reBuildHuffmanTree(str, arr, n);
        }
        else {                                                                      //判断它为叶节点
            strIndex++;
            arrayTree[i].it = arr[leafArrIndex];                     //写入其字符信息
            leafArrIndex++;
            return;
        }
    }
    else return;
}
void HuffmanTree::compare(unsigned char* Value,char* decToBinChar,int num) {
    if (arrayTree[num].lchild == -1) {          // 根据其为满二叉树的特性只判断左子树即可
        Value[0]=arrayTree[num].it;
        Value[1] = '\0';
        return;
    }
    if (decToBinChar[0] == '\0') { Value[1] = '0'; return; }
    else if (decToBinChar[0] == '0') {
        int i = 0;
        while (decToBinChar[i] != '\0') {
            decToBinChar[i] = decToBinChar[i + 1];
            i++;
        }
        compare(Value,decToBinChar, arrayTree[num].lchild);
    }
    else{
        int i = 0;
        while (decToBinChar[i] != '\0') {
            decToBinChar[i] = decToBinChar[i + 1];
            i++;
        }
        compare(Value,decToBinChar, arrayTree[num].rchild);
    }
};

bool compress(const char* sourceFilename, const char* geneFilename)
{
//    compress one file
    NodeList list;
    list.run(sourceFilename);
    length = list.size();
    HuffmanTree tree(length);
    tree.run(list);
    Ocharlength =list.getOcharlength(Ochar);
    tree.writeCodeToFile(geneFilename); //将编码表存入文件

    FILE* fo;
    fo=fopen( sourceFilename, "rb");
    FILE* fw;
    fw=fopen( geneFilename, "ab");
    if (fo == NULL || fw == NULL) {
        return false;
    }
    fprintf(fw,"%d",EOF);
    int decimal = 0;                            //将二进制转化为十进制
    int i, j, k = 0;
    int bits = 0;                                  //字符编码位数
    int temp[520];

    memset(temp, 0, sizeof(temp));
    while (!feof(fo)) {
        decimal = 0;
        unsigned char one_byte = fgetc(fo);
        for (i = 0; i < tree.len; i++) {
            if (one_byte == tree.arrayTree[i].it) {
                bits += strlen(tree.codeArray[i].ptr);
                int len = strlen(tree.codeArray[i].ptr);
                if (bits < 8) {
                    for (j = 0; j < len; j++)
                        temp[k++] = tree.codeArray[i].ptr[j] - '0';
                }
                else if (bits >= 8) {
                    for (j = 0; k < 8; j++)
                        temp[k++] = tree.codeArray[i].ptr[j] - '0';
                    for (; j < len; j++)
                        temp[k++] = tree.codeArray[i].ptr[j] - '0';
                    while (bits >= 8) {
                        decimal = temp[0] * 128 + temp[1] * 64 + temp[2] * 32 + temp[3] * 16 + temp[4] * 8 + temp[5] * 4 + temp[6] * 2 + temp[7] * 1;

                        for (j = 0; j < 8; j++)
                            temp[j] = 0;                       //将已处理部分置为0，方便后面的数据使用数组空间

                        for (j = 8; j < k; j++)
                            temp[j - 8] = temp[j];        //将大于8位的部分向前移动
                        k = bits = j - 8;

                        unsigned char c = decimal;   //将不足 8 的倍数的部分抛弃，达到压缩作用
                        fputc(c, fw);
                        fflush(fw);
                    }
                }
                break;
            }
        }
    }
    if (bits) {             //循环结束后 防止还有未凑够 8 位的
        decimal = temp[0] * 128 + temp[1] * 64 + temp[2] * 32 + temp[3] * 16 + temp[4] * 8 + temp[5] * 4 + temp[6] * 2 + temp[7] * 1;
        unsigned char c = decimal;
        fputc(c, fw);
        fflush(fw);
    }
    fclose(fw);
    fclose(fo);
    return true;
}

bool com_uncompress::compressFile(const char *path)
{
    string files[100];
    fileSystem fileManager;
    int n = 0;
    fileManager.getAllFiles(path, &n, files);
    for(int i = 0; i < n; i++)
    {
        char* newFile = new char[200];
        strcpy(newFile, files[i].c_str());
        strcat(newFile, ".8848com");
        fopen(newFile, "w");
        compress(files[i].c_str(), newFile);

        char*order = new char[50];
        strcpy(order,"rm -rf ");
        strcat(order,files[i].c_str());
        system(order);
    }
}

bool com_uncompress::uncompressFile(const char* geneFilename,const char* backFilename) {                                    //从树信息文件读取的所有结点个数

    FILE* fr;
    fr=fopen( geneFilename, "rb");
    if (fr == NULL) {
//        printf("1文件打开失败！");
        return false;
    }
    FILE* fw;
    fw=fopen(backFilename, "wb");
    if (fw == NULL) {
//        printf("2文件打开失败！");
        return false;
    }
    Ocharlength = 0;
    fscanf(fr, "%d", &Ocharlength,sizeof(int));
    //unsigned char* treeStruCode =  new unsigned char[Len]; //从树信息文件读取的树结构编码,最6长为Len
    unsigned char treeStruCode[1000];
    fscanf(fr, "%s", treeStruCode,1000);
    length = 0;
    for (int i = 0; i < strlen((char*)treeStruCode); i++) {
        if (treeStruCode[i] == '0') length += 1;
    }
    if (length == 0) {fclose(fw); fclose(fr); return false; }
    int* leafASCII = new int[length+1]();                //从树信息文件读取的叶的字符的ASCII码
    int Len = 2 * length - 1;
    int i = 0;
    for (i = 0;;i++) {
        fscanf(fr, "%d", &leafASCII[i]);   //判断是否读完所有叶结点
        if (leafASCII[i] == EOF)break;
    }
    Ochar = leafASCII[0];
    HuffmanTree HT(length);

    strIndex = 0;
    nodeIndex = 0;
    leafArrIndex = 0;
    HT.reBuildHuffmanTree(treeStruCode, leafASCII, Len - 1);   //根结点在 arrayTree 的最后
    delete[]leafASCII;

    unsigned char Value[2];
    int decToBinInt[8];                 //保存 从压缩文件读取的十进制转化的二进制的整数形式
    char decToBinChar [520];       //保存 从压缩文件读取的十进制转化的二进制的字符形式
    char decToBinChar2 [520];

    i = 0;
    int j = 0, k,temp=0;
    int OcharLength=0;

    while (!feof(fr)) {
        int data = fgetc(fr);
        if (data == -1) break;

        memset(decToBinInt, 0, sizeof(decToBinInt));
        i = 0;
        while (data) {                                  //将读取的压缩后的十进制数转化为二进制
            decToBinInt[i++] = data % 2;
            data = data / 2;
        }
        i = temp;
        for (k = 7; k >= 0; i++, k--) {     //将二进制数字转化为字符
            if (decToBinInt[k])
                decToBinChar[i] = '1';
            else
                decToBinChar[i] = '0';
        }decToBinChar[i] = '\0';

        int decCharLen = strlen(decToBinChar);
        if (decCharLen > length+8) {
//            printf("出错");
            break;
        }
        else {
            strcpy(decToBinChar2,decToBinChar);
            do {
                HT.compare(Value,decToBinChar2, 2 * length - 2);
                if (Value[1]== '\0') {
                    if (Value[0] == Ochar) OcharLength++;
                    if (OcharLength > Ocharlength) break;
                    i = 0;
                    while (decToBinChar2[i] != '\0') {
                        decToBinChar[i] = decToBinChar2[i];
                        i++;
                    }
                    decToBinChar[i] = '\0';;
                    fputc(Value[0], fw);
                    fflush(fw);
                }
            }while (Value[1] == '\0');
        }
        temp = i;
    }
    fclose(fw);
    fclose(fr);
    return true;
//    cout << "解压完成!" << endl;
}
