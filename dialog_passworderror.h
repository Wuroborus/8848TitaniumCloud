#ifndef DIALOG_PASSWORDERROR_H
#define DIALOG_PASSWORDERROR_H

#include <QDialog>

namespace Ui {
class Dialog_PasswordError;
}

class Dialog_PasswordError : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_PasswordError(QWidget *parent = nullptr);
    ~Dialog_PasswordError();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_PasswordError *ui;
};

#endif // DIALOG_PASSWORDERROR_H
