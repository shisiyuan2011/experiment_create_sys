#include "matiral.h"
#include <sstream>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
using namespace std;

matiral::matiral(QString dbname, QObject *parent) : QObject(parent)
{
    folder = new QDir;
    matiraldb = new QSqlDatabase;
    createfolder();
    *matiraldb = QSqlDatabase::addDatabase("QSQLITE");
    QString namedb = QString("D:/matiraldatabse/%1.%2").arg(dbname).arg("db");
    qDebug()<<namedb;
    matiraldb->setDatabaseName(namedb);
    if(!matiraldb->open()){
        qDebug()<<"fail connect";
        return;
    }
    else{
        qDebug()<<"successful connect";
    }
    createtable();
}
matiral::~matiral(){
    delete folder;
    matiraldb->close();
    delete matiraldb;
}
void matiral::createfolder(){
    bool exist = folder->exists("D:/matiraldatabse");
    if(exist)
    {
        qDebug()<<"already exist the folder";
    }
    else
    {
        bool ok = folder->mkdir("D:/matiraldatabse");
        if(!ok) qDebug()<<"create folder fail";
    }
}
void matiral::createtable(){
    QString Qquery = "CREATE TABLE IF NOT EXISTS MATIRALDB(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
"MATIRALNAME TEXT, YIELDSTRENGH TEXT, LIMITSTRESS TEXT, ELASTICITYMODULUS TEXT);";
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"create table fail"<<query.lastError();
    }else{
        qDebug()<<"table create successful";
    }
    return;
}
para matiral::getinfo(int ID){
    struct para result;
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE ID=%1").arg(ID);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return result;
    }else{
        if(query.next()){
            qDebug()<<"getdata data successful";
            result.id = query.value(0).toInt();
            result.matiralname = query.value(1).toString();
            result.yieldstrengh = query.value(2).toDouble();
            result.limitstress = query.value(3).toDouble();
            result.elasticitymodulus = query.value(4).toDouble();
        }else{
            qDebug()<<"end of the table";
        }
        return result;
    }
}

bool matiral::getinfo(QString matiralname,double yieldstrength,double limitstress,double elasticitymodulus){
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE MATIRALNAME='%1' AND YIELDSTRENGH = '%2' AND "
                        "LIMITSTRESS='%3' AND ELASTICITYMODULUS='%4'").
            arg(matiralname).
            arg(yieldstrength).
            arg(limitstress).
            arg(elasticitymodulus);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return true;
    }else{
        return query.next();
        qDebug()<<query.value(0);
    }

}
void matiral::insertdata(QString matiralname,double yieldstrength,double limitstress,double elasticitymodulus){
    QString Qquery = QString("INSERT INTO MATIRALDB (MATIRALNAME,YIELDSTRENGH,LIMITSTRESS,ELASTICITYMODULUS) VALUES('%1','%2','%3','%4')").
            arg(matiralname).
            arg(QString::number(yieldstrength)).
            arg(QString::number(limitstress)).
            arg(QString::number(elasticitymodulus));
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"insert data fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"insert data successful";
    }
}
void matiral::insertdata(QString matiralname,double limitstress,double elasticitymodulus){
    QString Qquery = QString("INSERT INTO MATIRALDB(MATIRALNAME,LIMITSTRESS,ELASTICITYMODULUS) "
            "VALUES('%1','%2','%3')").
            arg(matiralname).
            arg(QString::number(limitstress)).
            arg(QString::number(elasticitymodulus));
    qDebug()<<Qquery;
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"insert data fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"insert data successful";
    }
}
int matiral::getMID(QString matiralname,double yieldstrength,double limitstress,double elasticitymodulus){
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE MATIRALNAME='%1' AND YIELDSTRENGH = '%2' AND "
                        "LIMITSTRESS='%3' AND ELASTICITYMODULUS='%4'").
            arg(matiralname).
            arg(yieldstrength).
            arg(limitstress).
            arg(elasticitymodulus);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return true;
    }else{
        query.next();
        return query.value(0).toInt();
    }
}



int* matiral::GetProject(int TypeNum,int GoalNum,int MaterialNum,int LimitStress)
{
    struct project LoadResult;
    string TypeId="";
    string GoalId="";
    string MaterialId="";
    string SpecId="";
    int LoadStress[15];

//    QTableWidgetItem *item[4];
//    int nCount;

    char ss[10];
    sprintf(ss,"%03d",MaterialNum);

    switch (TypeNum)
    {
    case 1 :
        TypeId= "001";
        switch (GoalNum)
        {
        case 1 :
            GoalId= "001";
            LoadResult.LoadValue=0.5*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;

                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;

                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }


            break;
        case 2 :
            GoalId= "002";
            LoadResult.LoadValue=0.5*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            LoadStress[0]=LoadResult.LoadValue*0.5;

            break;
        case 3 :
            GoalId= "003";
            LoadResult.LoadValue=0.5*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;


            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        }
        break;
    case 2 :
        TypeId= "002";
        switch (GoalNum)
        {
        case 1 :
            GoalId= "001";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        case 2 :
            GoalId= "002";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            break;
        case 3 :
            GoalId= "003";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        }
        break;
    case 3 :
        TypeId= "003";
        switch (GoalNum)
        {
        case 1 :
            GoalId= "001";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        case 2 :
            GoalId= "002";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            break;
        case 3 :
            GoalId= "003";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        }
        break;
    case 4 :
        TypeId= "004";
        switch (GoalNum)
        {
        case 1 :
            GoalId= "001";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        case 2 :
            GoalId= "002";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            break;
        case 3 :
            GoalId= "003";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        }
        break;
    case 5 :
        TypeId= "005";
        switch (GoalNum)
        {
        case 1 :
            GoalId= "001";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        case 2 :
            GoalId= "002";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            break;
        case 3 :
            GoalId= "003";
            LoadResult.LoadValue=0.6*LimitStress;
            LoadResult.Frequency=0.1;
            LoadResult.RunOut=3000000;
            SpecId=TypeId+GoalId+ss;
            LoadResult.SpecId=SpecId;

            for(int ii=0;ii<15;++ii)
            {
                double j;
                j=ii;
                LoadStress[ii]=LoadResult.LoadValue-0.05*j*LoadResult.LoadValue;
                cout<<SpecId<<" "<<LoadStress[ii]<<" "<<LoadResult.Frequency<<" "<<LoadResult.RunOut<<endl;
            }
            break;
        }
        break;
    }

    int* temp = new int[ARRAY_SIZE(LoadStress)];
     for ( int i =0; i < ARRAY_SIZE(LoadStress); i++)
     temp[i] = (int)LoadStress[i];
      return temp;

}

int matiral::GetLimitStress(int ID){
    int CurrentStress;
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE ID=%1").arg(ID);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return 0;
    }else{
        if(query.next()){
            qDebug()<<"getdata data successful";

            CurrentStress = query.value(3).toDouble();

        }else{
            qDebug()<<"end of the table";
        }
        return CurrentStress;
    }
}
bool matiral::getinto(QString matiralname){
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE MATIRALNAME='%1'").
            arg(matiralname);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return true;
    }else{
        return query.next();
        qDebug()<<query.value(0);
    }
}
