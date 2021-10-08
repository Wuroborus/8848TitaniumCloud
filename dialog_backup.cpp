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
        ui->checkBox->setChecked(true);
        //Dialog_backup::on_checkBox_stateChanged(1);
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

    delete[] order;

    string remotePath;
    struct dirent* file;
    DIR* dir = opendir(named);
    while ((file = readdir(dir)) != NULL) {
        // get rid of "." and ".."
        if( strcmp( file->d_name , "." ) == 0 ||
            strcmp( file->d_name , "..") == 0    )
            continue;
        else {
            remotePath = named;
            remotePath.append("/");
            remotePath.append(file->d_name);
            break;
        }
    }

    if(isCompress) {
        // compress
        com_uncompress compressManager;
        cout << "compress: " << named << endl;
        compressManager.compressFile(named);
    }

    string parentpath, packpathforpass;
    if(isPack) {
        cout << "Packing.........." << endl;
        char* packpath = new char[200];
        strcpy(packpath, named);
        strcat(packpath, "/");
        strcat(packpath, this->Packname.toStdString().c_str());
        strcat(packpath, ".8848pack");

        pack((char*)remotePath.c_str(), packpath);
        parentpath = remotePath;
        packpathforpass = packpath;

        delete [] packpath;

        string order = "rm -rf " + parentpath;
        cout << order << endl;
        system(order.c_str());

        remotePath = packpathforpass;
    }

    if(isPass) {
        cout << "Pass.........." << endl;
        string newpasspath = packpathforpass + ".8848pass";

        char* packpath = new char[MAX_PATH];
        strcpy(packpath, packpathforpass.c_str());

        char* passpath = new char[MAX_PATH];
        strcpy(passpath, newpasspath.c_str());

        char* pass = new char[MAX_PATH];
        strcpy(pass, Password.toStdString().c_str());

        cout << "pass" << packpath << " to " << newpasspath << endl;
        code(packpath, passpath, pass);

        string order = "rm -rf " + packpathforpass;
        cout << order << endl;
        system(order.c_str());

        remotePath = packpath;

        delete[] packpath;
        delete[] passpath;
        delete[] pass;
    }

    // Server
    if(isRemote) {
        Client c("127.0.0.1");
        cout << "backup " << remotePath << " to the server" << endl;
        c.backup(remotePath);
//         c.monitor();

        string order = "rm -rf " + remotePath;
        system(order.c_str());
    }


    dialog_success = new Dialog_success(this);
    dialog_success->setModal(true);
    dialog_success->exec();
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
         ui->pushButton_2->setEnabled(false);
    }
    else {
        isRemote = false;
        ui->pushButton_2->setEnabled(true);
    }
}
