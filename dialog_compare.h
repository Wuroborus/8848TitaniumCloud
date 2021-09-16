#ifndef DIALOG_COMPARE_H
#define DIALOG_COMPARE_H

#include <QDialog>
#include <dialog_compare_result.h>

namespace Ui {
class Dialog_compare;
}

class Dialog_compare : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_compare(QWidget *parent = nullptr);
    ~Dialog_compare();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    void sendresult(char*);

private:
    Ui::Dialog_compare *ui;
    QString comparePathFrom;
    QString comparePathTo;
    Dialog_compare_result* dialog_compare_result;
};

#endif // DIALOG_COMPARE_H
