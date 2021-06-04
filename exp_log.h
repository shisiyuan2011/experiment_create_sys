#ifndef EXP_LOG_H
#define EXP_LOG_H

#include <QObject>
#include <QThread>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <iostream>
#include "QDebug"

struct data{
    int id;
    QString databasename;
    QString operatorname;
    QString starttime;
    QString stoptime;
    int setcir;
    int stopcir;
    int setforce;
};

class exp_log :public QThread
{
public:
    exp_log();
    void initial_log_database();
    void initial_log_database(QString databaseName, QString databasePath);
    void table();
    void table2();
    void adddata(QString force,int n);
    void adddata(QString databasename, QString operatorname, QString starttime,int setcir,int setforce);
    void refreshdata(QString stoptime,int stopcir);
    data getdata(int id);
    ~exp_log();
    //void run();
private:
    QSqlDatabase *database2;
    QString starttimeflag;
};

#endif // EXP_LOG_H
