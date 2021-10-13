#include "dialog_passworderror.h"
#include "ui_dialog_passworderror.h"

Dialog_PasswordError::Dialog_PasswordError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_PasswordError)
{
    ui->setupUi(this);
}

Dialog_PasswordError::~Dialog_PasswordError()
{
    delete ui;
}

void Dialog_PasswordError::on_pushButton_clicked()
{
    Dialog_PasswordError::close();
}
