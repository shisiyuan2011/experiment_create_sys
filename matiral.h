#ifndef MATIRAL_H
#define MATIRAL_H

#include <QObject>
#include <QDir>
#include <QThread>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <iostream>
#include "QDebug"
#include "vector"
using namespace std;
typedef struct para{
    int id = 0;
    QString matiralname = "";
    double yieldstrengh = 0;
    double limitstress = 0;
    double elasticitymodulus = 0;
    double arasa = 0;
    double hard = 0;
    QString heattreament = "";
}para;
class matiral
{
public:
    matiral();  
    para getinfo(int ID);
    vector<QString> getinfovector(const int &ID);
    bool getinfobool(const int &ID);
    bool getinfo(QString &matiralname,const double &yieldstrength,const double &limitstress,const double &elasticitymodulus);
    bool getinfo(const QString &matiralname,const double &yieldstrength,const double &limitstress,
                 const double &elasticitym, const double &arasa, const double &hardness);
    int getID(const QString &matiralname,const double &yieldstrength,const double &limitstress,
              const double &elasticitym, const double &arasa, const double &hardness);
    int getdataNUM();
    void insertdata(const QString &matiralname,const double &limitstress,const double &elasticitymodulus);
    void insertdata(const QString &matiralname,const double &yieldstrength,const double &limitstress,const double &elasticitymodulus);
    void insertdata(QString matiralname,double limitstress,double elasticitymodulus,double yieldstrength=0,
                    double arasa = 0,double hard=0,QString heattreament = "");
private:
    QSqlDatabase *matiraldb;
    QDir *folder;
    QString connectionname = "matiraldb_name";
private:
    void createtable();
    void createfolder();
};

#endif // MATIRAL_H
