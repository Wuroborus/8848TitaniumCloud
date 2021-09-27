#include "dialog_password.h"
#include "ui_dialog_password.h"

Dialog_password::Dialog_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_password)
{
    ui->setupUi(this);
}

Dialog_password::~Dialog_password()
{
    delete ui;
}

void Dialog_password::on_pushButton_clicked()//确认按钮
{
    password = ui->lineEdit->text();
    password_confirm = ui->lineEdit_2->text();
    if(password == "")
    {
        ui->label_4->setStyleSheet("color:red;");
        return;
    }
    else {
        ui->label_4->setStyleSheet("color:#f0f0f0");
    }
    if(password == password_confirm)
    {
        emit sendpassword(password);
        Dialog_password::close();
    }
    else {
        ui->label_3->setStyleSheet("color:red;");
    }
}

void Dialog_password::on_pushButton_2_clicked()//返回按钮
{
    Dialog_password::close();
}
