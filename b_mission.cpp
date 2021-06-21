#include "b_mission.h"
#include "ui_b_mission.h"

b_mission::b_mission(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::b_mission)
{
    ui->setupUi(this);
    caexp = new ca_exppara;
    cbr = new cb_rewrite;
    connect(this,&b_mission::caexpshow,caexp,&ca_exppara::thisshow);
    connect(this,&b_mission::reshow,cbr,&cb_rewrite::thisshow);
    connect(caexp,&ca_exppara::showMainwindow,this,&b_mission::showmaindow);
    connect(cbr,&cb_rewrite::mpshow,this,&b_mission::mpshow);
    connect(this,&b_mission::bmpshow,caexp,&ca_exppara::mpshow);
}

b_mission::~b_mission()
{
    delete ui;
}
void b_mission::thisshow(int type,int SN){
    bSN=SN;
    exptype = type;
    this->show();
}

void b_mission::on_New_clicked()
{
    this->hide();
    emit caexpshow(exptype,bSN);
}

void b_mission::on_renew_clicked()
{
    this->hide();
    emit reshow(exptype,bSN);
}
void b_mission::showmaindow(){
    emit showMaindow();
}
void b_mission::mpshow(QString ID){
    emit bmpshow(ID);
}
