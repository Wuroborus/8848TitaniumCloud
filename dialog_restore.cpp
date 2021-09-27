#include "dialog_restore.h"
#include "ui_dialog_restore.h"
#include "QFileDialog"
#include<dirent.h>

#include "huffman.h"
#include "pack.h"
#include "lock_safe.h"


Dialog_restore::Dialog_restore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_restore)
{
    ui->setupUi(this);
}

Dialog_restore::~Dialog_restore()
{
    delete ui;
}
void Dialog_restore::getpwforDecrypt(QString pwfd)
{
    pwfordecrypt = pwfd;
}


void Dialog_restore::on_pushButton_4_clicked()//返回按钮
{
    Dialog_restore::close();
}

void Dialog_restore::on_pushButton_clicked()
{
    filePathReTo = QFileDialog::getExistingDirectory();
    ui->backReTo->setText(filePathReTo);
}

void Dialog_restore::on_pushButton_2_clicked()
{
    filePathReFrom = QFileDialog::getExistingDirectory();
    ui->backReFrom->setText(filePathReFrom);

}

void Dialog_restore::on_pushButton_5_clicked()
{
    std::string  pathfrom= filePathReFrom.toStdString();
    const char* constcpathfrom = pathfrom.c_str();
    std::string pathto = filePathReTo.toStdString();
    const char* constcpathto = pathto.c_str();

    if(pathto == "" || pathfrom == "")
    {
        ui->label_2->setStyleSheet("color:red");
        return;
    }
    else{
        ui->label_2->setStyleSheet("color:#f0f0f0");
    }

    char* named = new char[50];
    for(int i = 0;i<=99;i++)
    {
        strcpy(named,constcpathto);
        strcat(named,"/Restore_");
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
   /* //修改所有文件夹时间
    memset(order,0,100);
    strcpy(order,"find ");
    strcat(order,constcpathto);
    strcat(order," -type d -exec touch -r ");
    strcat(order,constcpathfrom);
    strcat(order," {} \\");
    system(order);
    //修改所有文件时间
    memset(order,0,100);
    strcpy(order,"find ");
    strcat(order,constcpathto);
    strcat(order," -type f -exec touch -r ");
    strcat(order,constcpathfrom);
    strcat(order," {} \\");
    system(order);*/
    
    fileSystem fileManager;
    int n;
    string files[100];
    fileManager.getAllFiles(named, &n, files);
    string suffixStr = files[0].substr(files[0].find_last_of('.'));

    if(n == 1 && !suffixStr.compare(".8848pass")) {

        dialog_pwfordecrypt = new Dialog_PwForDecrypt(this);
        dialog_pwfordecrypt->setModal(true);
        QObject::connect(dialog_pwfordecrypt,SIGNAL(sendpwForDecrypt(QString)),this,SLOT(getpwforDecrypt(QString)));
        dialog_pwfordecrypt->exec();

        // pass
        char* unpasspath = new char[200];
        strcpy(unpasspath, named);
        char* packname = new char[50];
        int length = files[0].substr(files[0].find_last_of('/')).length() - strlen(".8848pass");
        strncpy(packname, files[0].substr(files[0].find_last_of('/')).c_str(), length);
        packname[length] = '\0';
        strcat(unpasspath, packname);

        int res = decode(const_cast<char*>(files[0].c_str()), const_cast<char*> (unpasspath), (char*)pwfordecrypt.toStdString().c_str());
//        std::cout << res;
        if(res != -1) {
            strcpy(order, "rm -rf ");
            strcat(order, files[0].c_str());
            system(order);
        }
    }

    if(n == 1 && !suffixStr.compare(".8848pack")) {
        int index = pathfrom.find_last_of("/");
        string dirName = pathfrom.substr(index, pathfrom.back());
        char* unpackpath = new char[200];
        strcpy(unpackpath, named);
        strcat(unpackpath, "/");
        strcat(unpackpath, dirName.c_str());
        unpack((char*)files[0].c_str(), unpackpath);
    }



    com_uncompress compressManager;
    compressManager.uncompressFile(named);

}
