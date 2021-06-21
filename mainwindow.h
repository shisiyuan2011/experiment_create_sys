#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <a_exptap_choose.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void showace(int type);
private slots:
    void on_rotoate_clicked();
    void showmainwindow();

private:
    Ui::MainWindow *ui;
    a_exptap_choose *aec;
};
#endif // MAINWINDOW_H
