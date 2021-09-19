#ifndef DIALOG_COMPARE_RESULT_H
#define DIALOG_COMPARE_RESULT_H

#include <QDialog>

namespace Ui {
class Dialog_compare_result;
}

class Dialog_compare_result : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_compare_result(QWidget *parent = nullptr);
    ~Dialog_compare_result();

private slots:
    void on_pushButton_clicked();

    void getresult(char*);

    void on_pushButton_2_clicked();

private:
    Ui::Dialog_compare_result *ui;
};

#endif // DIALOG_COMPARE_RESULT_H
