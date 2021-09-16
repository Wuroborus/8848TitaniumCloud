#ifndef DIALOG_PASSWORD_H
#define DIALOG_PASSWORD_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class Dialog_password;
}

class Dialog_password : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_password(QWidget *parent = nullptr);
    ~Dialog_password();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void sendpassword(QString);

private:
    Ui::Dialog_password *ui;
    QString password;
    QString password_confirm;
};

#endif // DIALOG_PASSWORD_H
