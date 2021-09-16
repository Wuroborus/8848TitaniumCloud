#include "dialog_pwfordecrypt.h"
#include "ui_dialog_pwfordecrypt.h"

Dialog_PwForDecrypt::Dialog_PwForDecrypt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_PwForDecrypt)
{
    ui->setupUi(this);
}

Dialog_PwForDecrypt::~Dialog_PwForDecrypt()
{
    delete ui;
}

void Dialog_PwForDecrypt::on_pushButton_clicked()
{
    pwfordecrypt = ui->lineEdit->text();
    emit sendpwForDecrypt(pwfordecrypt);
    Dialog_PwForDecrypt::close();
}

void Dialog_PwForDecrypt::on_pushButton_2_clicked()
{
    Dialog_PwForDecrypt::close();
}
