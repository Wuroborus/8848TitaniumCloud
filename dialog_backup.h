#ifndef DIALOG_BACKUP_H
#define DIALOG_BACKUP_H

#include <QDialog>
#include <dialog_password.h>
#include <dialog_packname.h>

namespace Ui {
class Dialog_backup;
}

class Dialog_backup : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_backup(QWidget *parent = nullptr);
    ~Dialog_backup();


private slots:
    void on_checkBox_3_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void getpassword(QString);

    void on_pushButton_5_clicked();

    void on_checkBox_stateChanged(int arg1);

    void getpackname(QString);

private:
    Ui::Dialog_backup *ui;
    Dialog_password* dialog_password;
    Dialog_packname* dialog_packname;
    QString filePathFrom;
    QString filePathTo;
    QString Password;
    QString Packname;
};

#endif // DIALOG_BACKUP_H
