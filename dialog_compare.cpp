#include "dialog_compare.h"
#include "ui_dialog_compare.h"
#include "QFileDialog"


Dialog_compare::Dialog_compare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_compare)
{
    ui->setupUi(this);
}

Dialog_compare::~Dialog_compare()
{
    delete ui;
}

void Dialog_compare::on_pushButton_3_clicked()
{
    comparePathFrom = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(comparePathFrom);
}

void Dialog_compare::on_pushButton_4_clicked()
{
    comparePathTo = QFileDialog::getExistingDirectory();
    ui->lineEdit_2->setText(comparePathTo);
}

void Dialog_compare::on_pushButton_2_clicked()
{
    Dialog_compare::close();
}

void Dialog_compare::on_pushButton_clicked()
{
    std::string pathfrom = comparePathFrom.toStdString();
    const char* constpathfrom = pathfrom.c_str();
    std::string pathto = comparePathTo.toStdString();
    const char* constpathto = pathto.c_str();

    if(pathfrom == "" || pathto == "")
    {
        ui->label_3->setStyleSheet("color:red");
        return;
    }
    else {
        ui->label_3->setStyleSheet("color:#f0f0f0");
    }
    //进行比较

    char* order = new char[100];
    strcpy(order,"diff -r -y ");
    strcat(order,constpathfrom);
    strcat(order," ");
    strcat(order,constpathto);

    char* result = new char[10240];
    char buf[1024];
    FILE* ptr;
    if((ptr = popen(order,"r")) != NULL)
    {
        while(fgets(buf,1024,ptr))
        {
            strcat(result,buf);
            if(strlen(result) > 10240)
            {
                break;
            }
        }
        fclose(ptr);
        ptr = NULL;
    }

    dialog_compare_result = new Dialog_compare_result(this);
    dialog_compare_result->setModal(true);
    QObject::connect(this,SIGNAL(sendresult(char*)),dialog_compare_result,SLOT(getresult(char*)));
    emit sendresult(result);
    dialog_compare_result->show();

}
