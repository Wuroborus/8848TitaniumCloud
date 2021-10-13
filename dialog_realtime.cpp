#include "dialog_realtime.h"
#include "ui_dialog_realtime.h"

Dialog_RealTime::Dialog_RealTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_RealTime)
{
    ui->setupUi(this);
}

Dialog_RealTime::~Dialog_RealTime()
{
    delete ui;
}

void Dialog_RealTime::on_pushButton_clicked()
{
    Dialog_RealTime::close();
}

void Dialog_RealTime::closeEvent(QCloseEvent *event)
{
    CLOSE = 0;
    emit sendclose(CLOSE);
    event->accept();
}

