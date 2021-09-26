#include "dialog_restore.h"
#include "ui_dialog_restore.h"
#include "QFileDialog"

#include "huffman.h"


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

QString Dialog_restore::getpwForDecrypt()
{
    dialog_pwfordecrypt = new Dialog_PwForDecrypt(this);
    dialog_pwfordecrypt->setModal(true);
    QObject::connect(dialog_pwfordecrypt,SIGNAL(sendpwForDecrypt(QString)),this,SLOT(getpwforDecrypt(QString)));
    dialog_pwfordecrypt->show();
    return pwfordecrypt;
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

    char* order = new char[100];
    strcpy(order,"cp -a ");
    strcat(order,constcpathfrom);
    strcat(order," ");
    strcat(order,constcpathto);
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
    
    

    delete order;

    com_uncompress compressManager;
    compressManager.uncompressFile((char*)pathto.c_str());

}
