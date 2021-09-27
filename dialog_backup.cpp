#include "dialog_backup.h"
#include "ui_dialog_backup.h"
#include "QFileDialog"
#include "QDebug"
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <file_time.h>

#include "huffman.h"
#include "pack.h"
#include "lock_safe.h"

#include "Client.h"


Dialog_backup::Dialog_backup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_backup)
{
    ui->setupUi(this);
}

Dialog_backup::~Dialog_backup()
{
    delete ui;
}


void Dialog_backup::on_pushButton_clicked()//备份路径选择
{
    filePathFrom = QFileDialog::getExistingDirectory();
    ui->backFrom->setText(filePathFrom);
}


void Dialog_backup::on_pushButton_2_clicked()
{
    filePathTo = QFileDialog::getExistingDirectory();
    ui->backTo->setText(filePathTo);

}

void Dialog_backup::getpassword(QString password)
{
    Password = password;
}

void Dialog_backup::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1)
    {
        dialog_password = new Dialog_password(this);
        dialog_password->setModal(true);
        QObject::connect(dialog_password,SIGNAL(sendpassword(QString)),this,SLOT(getpassword(QString)));
        dialog_password->show();
        //qDebug() << Password;

        isPass = true;
    }
    else {
        isPass = false;
    }
}

void Dialog_backup::on_pushButton_4_clicked()//返回按钮
{
    Dialog_backup::close();
}

void Dialog_backup::on_pushButton_5_clicked()//备份操作
{    
    std::string pathfrom = filePathFrom.toStdString();
    const char* constcpathfrom = pathfrom.c_str();
    std::string pathto = filePathTo.toStdString();
    const char* constcpathto = pathto.c_str();

    if(pathfrom == "" || pathto == "")
    {
        ui->label_2->setStyleSheet("color:red");
        return;
    }
    else {
        ui->label_2->setStyleSheet("color:#f0f0f0");
    }

    if(!isRemote) {

    }
    char* named = new char[50];
    for(int i = 0;i<=99;i++)
    {
        strcpy(named,constcpathto);
        strcat(named,"/back_up_");
        strcat(named,std::to_string(i).c_str());
        if(opendir(named))
        {
            memset(named,0,50);
            continue;
        }
        else {
            break;
        }
    }

    char* order = new char[100];

    strcpy(order,"mkdir -p ");
    strcat(order,named);
    system(order);


    memset(order,0,100);
    strcpy(order,"cp -a ");
    strcat(order,constcpathfrom);
    strcat(order," ");
    strcat(order,named);
    system(order);

    //delete order;
//    file_time* GotFromtime = new file_time;
//    char* cpathfrom;
//    char* cpathto;
//    strcpy(cpathfrom,constcpathfrom);
//    strcpy(cpathto,constcpathto);
//    GotFromtime->changefiletime(cpathfrom,cpathto);

    if(isCompress) {
        // compress
        com_uncompress compressManager;
        compressManager.compressFile(named);
    }

    if(isPack) {
        char* packpath = new char[200];
        strcpy(packpath, named);
        strcat(packpath, "/");
        strcat(packpath, this->Packname.toStdString().c_str());
        strcat(packpath, ".8848pack");
        pack((char*)pathto.c_str(), packpath);

        int index = pathfrom.find_last_of("/");
        string dirName = pathfrom.substr(index, pathfrom.back());
        char* order = new char[100];
        strcpy(order, "rm -rf ");
        strcat(order, named);
        strcat(order, dirName.c_str());
        system(order);
    }

    if(isPass) {
        int index = pathfrom.find_last_of("/");
        string dirName = pathfrom.substr(index, pathfrom.back());
        char* passpath = new char[200], * newpasspath = new char[200];
        strcpy(passpath, named);
        strcat(passpath, dirName.c_str());
        strcpy(newpasspath, passpath);
        strcat(newpasspath, ".8848pass");

        code(passpath, newpasspath, (char*)Password.toStdString().c_str());
    }

    // Server
    if(isRemote) {
        Client c("127.0.0.1");
        c.request_service("backup " + pathto);

        fileSystem fileManager;
        int fileno;
        string files[100];
        fileManager.getAllFiles(pathfrom.c_str(), &fileno, files);
        for(int i = 0; i < fileno; i++)
        {
            c.send_file(files[i]);
        }
    }


    dialog_success = new Dialog_success(this);
    dialog_success->setModal(true);
    dialog_success->show();
}

void Dialog_backup::getpackname(QString packname)
{
    Packname = packname;
}

void Dialog_backup::on_checkBox_stateChanged(int arg1)//打包包名
{
    if(arg1)
    {
        isPack = true;
        dialog_packname = new Dialog_packname(this);
        dialog_packname->setModal(true);
        QObject::connect(dialog_packname,SIGNAL(sendpackname(QString)),this,SLOT(getpackname(QString)));
        dialog_packname->show();
    }
    else {
        isPack = false;
    }
}

void Dialog_backup::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1)
    {
        isCompress = true;
    }
    else {
        isCompress = false;
    }
}

void Dialog_backup::on_checkBox_4_stateChanged(int arg1)
{
    // remote or local
    if(arg1) {
        isRemote = true;
    }
    else {
        isRemote = false;
    }
}
