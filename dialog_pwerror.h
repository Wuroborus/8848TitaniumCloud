#ifndef DIALOG_PWERROR_H
#define DIALOG_PWERROR_H

#include <QDialog>

namespace Ui {
class Dialog_PwError;
}

class Dialog_PwError : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_PwError(QWidget *parent = nullptr);
    ~Dialog_PwError();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_PwError *ui;
};

#endif // DIALOG_PWERROR_H
