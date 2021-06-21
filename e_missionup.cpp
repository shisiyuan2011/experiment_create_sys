#include "e_missionup.h"
#include "ui_e_missionup.h"

e_missionup::e_missionup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::e_missionup)
{
    ui->setupUi(this);
    dip = new dispatch;
    dip->show();
}

e_missionup::~e_missionup()
{
    delete ui;
}
void e_missionup::thisshow(int type,int SN){
    exptype = type;
    eSN = SN;
    this->show();
}

void e_missionup::on_pushButton_2_clicked()
{
    this->hide();
    emit showMainwindow();
}
void e_missionup::mpshow(QString ID){
    qDebug()<<ID;
    this->show();
}
