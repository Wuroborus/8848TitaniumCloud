#include "dialog_compare_result.h"
#include "ui_dialog_compare_result.h"
#include <qclipboard.h>

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

void Dialog_compare_result::on_pushButton_2_clicked()
{
    QString source = ui->textEdit->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(source);
    ui->label->setStyleSheet("color:black");
}

