#include "dialog_success.h"
#include "ui_dialog_success.h"

Dialog_success::Dialog_success(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_success)
{
    ui->setupUi(this);
}

Dialog_success::~Dialog_success()
{
    delete ui;
}

void Dialog_success::on_pushButton_clicked()
{
    Dialog_success::close();
}
