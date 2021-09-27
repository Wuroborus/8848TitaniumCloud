#include "dialog_packname.h"
#include "ui_dialog_packname.h"

Dialog_packname::Dialog_packname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_packname)
{
    ui->setupUi(this);
}

Dialog_packname::~Dialog_packname()
{
    delete ui;
}

void Dialog_packname::on_pushButton_clicked()//确认按钮
{
    Packname = ui->lineEdit->text();
    if(Packname.contains(".") > 0 || Packname.contains("/") > 0)
    {
        ui->label_3->setStyleSheet("color:red");
        return;
    }
    emit sendpackname(Packname);
    Dialog_packname::close();
}


void Dialog_packname::on_pushButton_2_clicked()//返回按钮
{
    Dialog_packname::close();
}
