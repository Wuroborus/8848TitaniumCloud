#ifndef DIALOG_PACKNAME_H
#define DIALOG_PACKNAME_H

#include <QDialog>

namespace Ui {
class Dialog_packname;
}

class Dialog_packname : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_packname(QWidget *parent = nullptr);
    ~Dialog_packname();

signals:
    void sendpackname(QString);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog_packname *ui;
    QString Packname;
};

#endif // DIALOG_PACKNAME_H
