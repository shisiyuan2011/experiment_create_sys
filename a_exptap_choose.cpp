#include "a_exptap_choose.h"
#include "ui_a_exptap_choose.h"

a_exptap_choose::a_exptap_choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::a_exptap_choose)
{
    ui->setupUi(this);
    bm = new b_mission;
    connect(this,&a_exptap_choose::bmshow,bm,&b_mission::thisshow);
    connect(bm,&b_mission::showMaindow,this,&a_exptap_choose::showmaindow);
}

a_exptap_choose::~a_exptap_choose()
{
    delete ui;
}
void a_exptap_choose::thisshow(int type){
    exptype = type;
    this->show();
}

void a_exptap_choose::on_SN_clicked()
{
    this->hide();
    emit bmshow(exptype,0);
}

void a_exptap_choose::on_ebuselu1_clicked()
{
    this->hide();
    emit bmshow(exptype,1);
}
void a_exptap_choose::showmaindow(){
    emit showMainwindow();
}
