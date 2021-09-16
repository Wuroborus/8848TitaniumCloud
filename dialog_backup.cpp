#include "dialog_backup.h"
#include "ui_dialog_backup.h"
#include "QFileDialog"
#include "QDebug"
#include <sys/types.h>
#include <dirent.h>


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
    strcat(order,constcpathto);
    strcat(order,named);
    system(order);
    //修改所有文件夹时间
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
    system(order);

    delete order;
}

void Dialog_backup::getpackname(QString packname)
{
    Packname = packname;
}

void Dialog_backup::on_checkBox_stateChanged(int arg1)//打包包名
{
    if(arg1)
    {
        dialog_packname = new Dialog_packname(this);
        dialog_packname->setModal(true);
        QObject::connect(dialog_packname,SIGNAL(sendpackname(QString)),this,SLOT(getpackname(QString)));
        dialog_packname->show();
    }
}
