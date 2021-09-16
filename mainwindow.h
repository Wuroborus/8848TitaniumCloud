#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog_backup.h>
#include <dialog_restore.h>
#include <dialog_compare.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


private:
    Ui::MainWindow *ui;
    Dialog_backup* dialog_backup;
    Dialog_restore* dialog_restore;
    Dialog_compare* dialog_compare;
};

#endif // MAINWINDOW_H
