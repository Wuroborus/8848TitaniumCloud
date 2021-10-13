#ifndef DIALOG_REALTIME_H
#define DIALOG_REALTIME_H

#include <QDialog>
#include<QCloseEvent>

namespace Ui {
class Dialog_RealTime;
}

class Dialog_RealTime : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_RealTime(QWidget *parent = nullptr);
    ~Dialog_RealTime();

private slots:
    void on_pushButton_clicked();

signals:
    void sendclose(int);

private:
    void closeEvent(QCloseEvent *event);
    int CLOSE;
    Ui::Dialog_RealTime *ui;
};

#endif // DIALOG_REALTIME_H
