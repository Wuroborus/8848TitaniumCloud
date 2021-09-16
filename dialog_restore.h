#ifndef DIALOG_RESTORE_H
#define DIALOG_RESTORE_H

#include <QDialog>
#include <dialog_pwfordecrypt.h>

namespace Ui {
class Dialog_restore;
}

class Dialog_restore : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_restore(QWidget *parent = nullptr);
    ~Dialog_restore();
    QString getpwForDecrypt();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void getpwforDecrypt(QString);

private:
    Ui::Dialog_restore *ui;
    Dialog_PwForDecrypt* dialog_pwfordecrypt;
    QString filePathReFrom;
    QString filePathReTo;
    QString pwfordecrypt;
};

#endif // DIALOG_RESTORE_H
