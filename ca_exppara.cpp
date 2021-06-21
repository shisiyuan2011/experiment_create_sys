#include "ca_exppara.h"
#include "ui_ca_exppara.h"

ca_exppara::ca_exppara(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ca_exppara)
{
    ui->setupUi(this);
    dm = new d_matiralinfo;
    connect(this,&ca_exppara::dmishow,dm,&d_matiralinfo::thisshow);
    connect(dm,&d_matiralinfo::showMainwindow,this,&ca_exppara::showmainwindow);
    connect(this,&ca_exppara::campshow,dm,&d_matiralinfo::mpshow);
}

ca_exppara::~ca_exppara()
{
    delete ui;
}
void ca_exppara::thisshow(int type, int SN){
    exptype = type;
    caSN = SN;
    this->show();
}

void ca_exppara::on_pushButton_clicked()
{
    double co;
    int overcir;
    switch (ui->confidence->currentIndex()) {
    case 0:
        co = 0.5;
        break;
    case 1:
        co = 0.9;
        break;
    case 2:
        co = 0.95;
        break;
    }
    switch (ui->overcir->currentIndex()) {
    case 0:
        overcir = 10000;
        break;
    case 1:
        overcir = 100;
        break;
    }
    this->hide();
    emit dmishow(exptype,caSN,co,overcir);
}
void ca_exppara::showmainwindow(){
    emit showMainwindow();
}
void ca_exppara::mpshow(QString ID){
    emit campshow(ID);
}
