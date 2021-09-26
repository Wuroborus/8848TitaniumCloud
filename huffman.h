#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <string.h>
#include <bitset> //输出二进制的头文件
#include<limits>
#include<string>
#include <filesystem.h>
using namespace std;

/*Huffman结点*/
class TreeNode {
public:
    unsigned char it;                            //结点元素
    double weight;                              //结点权重
    int parent, lchild, rchild;                 //结点的父结点及左右子结点
    TreeNode() {
        parent = lchild = rchild = -1;
    }
    TreeNode(const unsigned char& data, const double& wt) {
        it = data;
        weight = wt;
        parent = lchild = rchild = -1;
    }
};


struct Node                   //生成一个类链表，存放非重复字节的元素，次数，个数
{
    int Data, weight;
    Node* next;
};
class NodeList
{
private:
    Node* head;
    int len=0;
public:
    NodeList() { head = NULL; }
    void insertlist(const unsigned char& Data);
    void run(const char*);
    int size();
    int findPosition(const unsigned char&) const;
    int getOcharlength(unsigned char&);
    Node* gethead() { return head; }
};



/*编码类 存放每个字母的编码*/
class Code {
public:
    char* ptr;
    Code() { ptr = new char[256]; }
};

/*Huffman树*/
class HuffmanTree {
private:                                                                //数组最大值
    int findPosition(const unsigned char&) const;          //返回字符在arrayTree[]中的位置

    void buildHuffmanTree();                                           //创建哈夫曼树
    void writeTreeStructureToFile(const int&, FILE*);     //将树结构信息存储到树信息文件中
    void writeLeafToFile(const int&, FILE*);                    //将叶结点信息存储到树信息文件中
    void insert(const unsigned char&, const double&);  //插入结点
    unsigned char getOchar(const int);
public:                  //非重复字符个数
    int len;
    TreeNode* arrayTree;   //哈夫曼结点数组
    Code* codeArray;         //存放每个叶结点的编码，大小为len
    HuffmanTree(int size) {
        arrayTree = new TreeNode[2*size-1];
        len = size;
    }
    void run(NodeList);                                              //编码用，建树 编码 写入树信息文件
    void reBuildHuffmanTree(const unsigned char*, const int*, int); //解码用，根据树信息文件重建Huffman树
    void createHuffmanCode();                                                         //编解码均可用，创建Huffman编码
    void writeCodeToFile(const char*);                           //将Huffman树存储到树信息文件中
    void compare(unsigned char*,char*,int);
};

class com_uncompress{
public:
    bool compressFile(const char* path);
    bool uncompressFile(const char* path);
};

#endif
