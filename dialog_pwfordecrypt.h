#ifndef DIALOG_PWFORDECRYPT_H
#define DIALOG_PWFORDECRYPT_H

#include <QDialog>

namespace Ui {
class Dialog_PwForDecrypt;
}

class Dialog_PwForDecrypt : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_PwForDecrypt(QWidget *parent = nullptr);
    ~Dialog_PwForDecrypt();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void sendpwForDecrypt(QString);

private:
    Ui::Dialog_PwForDecrypt *ui;
    QString pwfordecrypt;
};

#endif // DIALOG_PWFORDECRYPT_H
