#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tableInfo->setColumnCount(4);
    ui->tableInfo->setRowCount(16);
    QStringList header;
    ui->tableInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    header<<"SpecId"<<"Load"<<"Frequency"<<"RunOut";
//    ui->tableInfo->setHorizontalHeaderLabels(header);
    ui->tableInfo->verticalHeader()->setVisible(false);
//    insertTableItems();



//    para re = m->getinfo(1);
//    qDebug()<<re.id<<re.matiralname<<re.yieldstrengh<<re.limitstress<<re.elasticitymodulus;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    m = new matiral;

    QString MaterialsText=ui->Materials->text();
    QString YieldStrengthText=ui->YieldStrength->text();
    QString LimitStressText=ui->LimitStress->text();
    QString ElasticityModulusText=ui->ElasticityModulus->text();

    double YieldStrengthNum = YieldStrengthText.toDouble();
    double LimitStressNum_1=LimitStressText.toDouble();
    double ElasticityModulusNum=ElasticityModulusText.toDouble();


    int MaterialNum;
    if((m->getinfo(MaterialsText,YieldStrengthNum,LimitStressNum_1,ElasticityModulusNum))!=true)
    {m->insertdata(MaterialsText,YieldStrengthNum,LimitStressNum_1,ElasticityModulusNum);
        MaterialNum=m->getMID(MaterialsText,YieldStrengthNum,LimitStressNum_1,ElasticityModulusNum);}
    else
    {
         MaterialNum=m->getMID(MaterialsText,YieldStrengthNum,LimitStressNum_1,ElasticityModulusNum);
//        qDebug()<<MaterialNum;
    }
    int LimitStressNum;
    LimitStressNum=m->GetLimitStress(MaterialNum);
    qDebug()<<LimitStressNum;
    int GoalNum=2;

    int *p=m->GetProject(1,GoalNum,MaterialNum,LimitStressNum);

    QString b;
    QTableWidgetItem *item[4];
    int i;
    int nCount;


    if(GoalNum!=2){
    for(i=0;i<15;i++)
    {
        nCount=ui->tableInfo->rowCount();

        item[0]=new QTableWidgetItem(QString("%1").arg(i+1));
        ui->tableInfo->setItem(i,0,item[0]);

        b = QString::number(p[i],10,5);
        item[1]=new QTableWidgetItem(b);
        ui->tableInfo->setItem(i,1,item[1]);//

        item[2]=new QTableWidgetItem("0.1");
        ui->tableInfo->setItem(i,2,item[2]);

        item[3]=new QTableWidgetItem("3000000");
        ui->tableInfo->setItem(i,3,item[3]);

}}
    else
    {
        nCount=ui->tableInfo->rowCount();

        item[0]=new QTableWidgetItem(QString("%1").arg(0+1));
        ui->tableInfo->setItem(0,0,item[0]);

        b = QString::number(p[0],10,5);
        item[1]=new QTableWidgetItem(b);
        ui->tableInfo->setItem(0,1,item[1]);//

        item[2]=new QTableWidgetItem("0.1");
        ui->tableInfo->setItem(0,2,item[2]);

        item[3]=new QTableWidgetItem("3000000");
        ui->tableInfo->setItem(0,3,item[3]);
    }




}
/*void MainWindow::insertTableItems(void)
{
    QTableWidgetItem *item[2];
    int i;
    int nCount;

    for(i=0;i<15;i++)
    {
        nCount=ui->tableInfo->rowCount();

        item[0]=new QTableWidgetItem(QString("%1").arg(i+1));
        ui->tableInfo->setItem(i,0,item[0]);

        item[1]=new QTableWidgetItem(value[15]);
        ui->tableInfo->setItem(i,1,item[1]);

    }

}*/

