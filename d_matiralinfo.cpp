#include "d_matiralinfo.h"
#include "ui_d_matiralinfo.h"

d_matiralinfo::d_matiralinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::d_matiralinfo)
{
    ui->setupUi(this);
    emu = new e_missionup;
    ui->tableWidget->setRowCount(200);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mdb = new matiral;

    connect(this,&d_matiralinfo::emshow,emu,&e_missionup::thisshow);
    connect(emu,&e_missionup::showMainwindow,this,&d_matiralinfo::showmainwindow);
    connect(this,&d_matiralinfo::dmpshow,emu,&e_missionup::mpshow);

    refreshtable();
}

d_matiralinfo::~d_matiralinfo()
{
    delete ui;
}
void d_matiralinfo::thisshow(int type,int SN,double po,int overcir){
    dovercir = overcir;
    conf = po;
    exptype = type;
    dSN = SN;
    //qDebug()<<"overcir="<<overcir<<" conf="<<conf<<" exptype="<<exptype<<" SN="<<dSN;
    this->show();
}

void d_matiralinfo::on_pushButton_clicked()
{

    this->hide();
    emit emshow(exptype,dSN);
}
void d_matiralinfo::showmainwindow(){
    emit showMainwindow();
}
void d_matiralinfo::mpshow(QString ID){
    emit dmpshow(ID);
}
void d_matiralinfo::refreshtable(){
    ui->tableWidget->clearContents();
    int i = 1,j = 0;
    while(mdb->getinfobool(i)){
        vector<QString> p = mdb->getinfovector(i);
        for(int k = 0; k < 8; ++k){
            QTableWidgetItem *item = new QTableWidgetItem(p[k]);
            ui->tableWidget->setItem(i-1,k,item);
        }
        ++j;
        ++i;
    }
}

void d_matiralinfo::on_pushButton_2_clicked()
{
    //判断必填项目是否为空
    if(ui->m_name->text().isEmpty()||ui->ebuselub->text().isEmpty()||ui->ebuselus->text().isEmpty()
            ||ui->yongs->text().isEmpty()){
        QMessageBox::information(this,"warning","matiral name yieldstrenge limitstress "
                                "elasticitymodulus is neccessary");
        return;
    }
    //判断是否存在该条目
    bool a = mdb->getinfo(ui->m_name->text(),ui->ebuselus->text().toDouble(),
                 ui->ebuselub->text().toDouble(),ui->yongs->text().toDouble(),
                 ui->arasa->text().isEmpty()?0:ui->arasa->text().toDouble(),
                 ui->hard->text().isEmpty()?0:ui->hard->text().toDouble());
    qDebug()<<a;
    //如果不存在的话则插入该条目，并返回插入条目的ID
    if(!a){
        mdb->insertdata(ui->m_name->text(),ui->ebuselus->text().toDouble(),
                        ui->ebuselub->text().toDouble(),ui->yongs->text().toDouble(),
                        ui->arasa->text().isEmpty()?0:ui->arasa->text().toDouble(),
                        ui->hard->text().isEmpty()?0:ui->hard->text().toDouble(),
                        ui->atsushixyori->text().isEmpty()?"":ui->atsushixyori->text());
        qDebug()<<"no exist, this ID is: "<<mdb->getdataNUM();
    }else{
        //如果存在的话得到该条目的id
        int ID = mdb->getID(ui->m_name->text(),ui->ebuselus->text().toDouble(),
                            ui->ebuselub->text().toDouble(),ui->yongs->text().toDouble(),
                            ui->arasa->text().isEmpty()?0:ui->arasa->text().toDouble(),
                            ui->hard->text().isEmpty()?0:ui->hard->text().toDouble());
        qDebug()<<"this exsit ID is: "<<ID;
    }
    refreshtable();
}
