#include "exp_log.h"

exp_log::exp_log()
{
    database2 = new QSqlDatabase;
}
void exp_log::initial_log_database(){
    *database2 = QSqlDatabase::addDatabase("QSQLITE");
    QString namedb = "C:/Users/yangm/Desktop/database/exp_log.db";//要根据实际的进行更改
    database2->setDatabaseName(namedb);
    if(!database2->open()){
        qDebug()<<"fail connect";
        return;
    }
    else{
        qDebug()<<"successful connect";
        return;
    }
}
void exp_log::initial_log_database(QString databaseName, QString databasePath){
    *database2 = QSqlDatabase::addDatabase("QSQLITE");
    QString namedb = databasePath + "/" + databaseName + ".db";
    qDebug()<<namedb;
    //databasePath形如"C:/Users/yangm/Desktop/server/build-5_20_server-unknown-Debug" databaseName形如mydb
    database2->setDatabaseName(namedb);
    if(!database2->open()){
        qDebug()<<"fail connect";
        return;
    }
    else{
        qDebug()<<"successful connect";
        return;
    }
}
void exp_log::table(){
    QString Qquery = "CREATE TABLE IF NOT EXISTS DATALOG(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
"DATABASENAME TEXT, OPERATORNAME TEXT, STARTTIME TEXT, STOPTIME TEXT, SETCIR INT, STOPCIR INT,"
"SETFORCE INT);";
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"create table fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"table create successful";
    }
}
void exp_log::table2(){
    QString Qquery = "CREATE TABLE IF NOT EXISTS DATA1(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
"FORCE INT);";
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"create table fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"table create successful";
    }
    QString Qquery2 = "CREATE TABLE IF NOT EXISTS DATA2(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
"FORCE INT);";
    QSqlQuery query2;
    if(!query2.exec(Qquery2)){
        qDebug()<<"create table fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"table create successful";
    }
    QString Qquery3 = "CREATE TABLE IF NOT EXISTS DATA3(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
"FORCE INT);";
    QSqlQuery query3;
    if(!query3.exec(Qquery3)){
        qDebug()<<"create table fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"table create successful";
    }
    QString Qquery4 = "CREATE TABLE IF NOT EXISTS DATA4(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
"FORCE INT);";
    QSqlQuery query4;
    if(!query4.exec(Qquery4)){
        qDebug()<<"create table fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"table create successful";
    }
}
void exp_log::adddata(QString force,int n){
    QString Qquery,Qquery2,Qquery3,Qquery4;
    QSqlQuery query,query2,query3,query4;
    switch (n) {
    case 1:
        Qquery = QString("INSERT INTO DATA1(FORCE) VALUES('%1')").arg(force);
        if(!query.exec(Qquery)){
            qDebug()<<"insert data fail"<<query.lastError();
            return;
        }else{
            qDebug()<<"insert data successful";
        }
        break;
    case 2:
        Qquery2 = QString("INSERT INTO DATA2(FORCE) VALUES('%1')").arg(force);
        if(!query2.exec(Qquery2)){
            qDebug()<<"insert data fail"<<query2.lastError();
            return;
        }else{
            qDebug()<<"insert data successful";
        }
        break;
    case 3:
        Qquery3 = QString("INSERT INTO DATA3(FORCE) VALUES('%1')").arg(force);
        if(!query3.exec(Qquery3)){
            qDebug()<<"insert data fail"<<query3.lastError();
            return;
        }else{
            qDebug()<<"insert data successful";
        }
        break;
    case 4:
        Qquery4 = QString("INSERT INTO DATA4(FORCE) VALUES('%1')").arg(force);
        if(!query4.exec(Qquery4)){
            qDebug()<<"insert data fail"<<query4.lastError();
            return;
        }else{
            qDebug()<<"insert data successful";
        }
        break;

    }

}
void exp_log::adddata(QString databasename, QString operatorname, QString starttime,int setcir,int setforce){
    //starttime是唯一的，可以通过starttime进行更新
    //这个时候获取主键，随后在停止后，在refreshdata中利用该主键进行更新
    starttimeflag = starttime;
    QString Qquery = QString("INSERT INTO DATALOG(DATABASENAME,OPERATORNAME,STARTTIME,SETCIR,SETFORCE) "
"VALUES('%1','%2','%3',%4,%5)").arg(databasename).arg(operatorname).arg(starttime).arg(setcir).arg(setforce);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"insert data fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"insert data successful";
    }
}
void exp_log::refreshdata(QString stoptime,int stopcir){
    QString Qquery = QString("UPDATE DATALOG SET STOPTIME='%1',STOPCIR=%2 "
"WHERE STARTTIME='%3'").arg(stoptime).arg(stopcir).arg(starttimeflag);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"updata data fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"updata data successful";
    }
}
data exp_log::getdata(int id){
    data result;
    result.databasename="error";
    QString Qquery = QString("SELECT * FROM DATALOG WHERE ID=%1").arg(id);
    QSqlQuery query;
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return result;
    }else{
        if(query.next()){
            qDebug()<<"getdata data successful";
            result.id = query.value(0).toInt();
            result.databasename = query.value(1).toString();
            result.operatorname = query.value(2).toString();
            result.starttime = query.value(3).toString();
            result.stoptime = query.value(4).toString();
            result.setcir = query.value(5).toInt();
            result.stopcir = query.value(6).toInt();
            result.setforce = query.value(7).toInt();
        }else{
            qDebug()<<"end of the table";
        }
    }
    return result;
}
exp_log::~exp_log(){
    database2->close();
}
