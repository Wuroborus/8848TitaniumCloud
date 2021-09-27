#include "dialog_pwerror.h"
#include "ui_dialog_pwerror.h"

Dialog_PwError::Dialog_PwError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_PwError)
{
    ui->setupUi(this);
}

Dialog_PwError::~Dialog_PwError()
{
    delete ui;
}

void Dialog_PwError::on_pushButton_clicked()
{
    Dialog_PwError::close();
}
