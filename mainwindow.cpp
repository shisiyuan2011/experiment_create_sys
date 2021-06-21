#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aec = new a_exptap_choose;
    connect(this,&MainWindow::showace,aec,&a_exptap_choose::thisshow);
    connect(aec,&a_exptap_choose::showMainwindow,this,&MainWindow::showmainwindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_rotoate_clicked()
{
    this->hide();
    emit showace(2);
}
void MainWindow::showmainwindow(){
    this->show();
}
