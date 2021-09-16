#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//备份界面
{
    dialog_backup = new Dialog_backup(this);
    dialog_backup->setModal(true);
    dialog_backup->show();
}

void MainWindow::on_pushButton_2_clicked()//还原界面
{
    dialog_restore = new Dialog_restore(this);
    dialog_restore->setModal(true);
    dialog_restore->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    dialog_compare = new Dialog_compare(this);
    dialog_compare->setModal(true);
    dialog_compare->show();
}
