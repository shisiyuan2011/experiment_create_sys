#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "matiral.h"
#include "exp_log.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    void insertTableItems(void);



private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    matiral *m;
    //exp_log *e;
};
#endif // MAINWINDOW_H
