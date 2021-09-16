#include "dialog_compare_result.h"
#include "ui_dialog_compare_result.h"

Dialog_compare_result::Dialog_compare_result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_compare_result)
{
    ui->setupUi(this);
}

Dialog_compare_result::~Dialog_compare_result()
{
    delete ui;
}

void Dialog_compare_result::on_pushButton_clicked()
{
    Dialog_compare_result::close();
}


void Dialog_compare_result::getresult(char* result)
{
       ui->textEdit->setText(result);
}
