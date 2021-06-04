#ifndef MATIRAL_H
#define MATIRAL_H

#include <QObject>
#include <QDir>
#include <QThread>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <iostream>
#include "QDebug"
#include <QLabel>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDate>

struct para{
    int id = 0;
    QString matiralname = "";
    double yieldstrengh = 0;
    double limitstress = 0;
    double elasticitymodulus = 0;
};

struct project{
    std::string SpecId="";
    int LoadValue=0;
    double Frequency=0;
    int RunOut=0;
};


class matiral : public QObject
{
    Q_OBJECT
public:
    int* GetProject(int TypeNum,int GoalNum,int MaterialNum,int LimitStress);
    int GetLimitStress(int ID);


    explicit matiral(QString dbname = "testdb",QObject *parent = nullptr);
    void createtable();
    void createfolder();
    para getinfo(int ID);
    bool getinfo(QString matiralname,double yieldstrength,double limitstress,double elasticitymodulus);
    bool getinto(QString matiralname);
    int getMID(QString matiralname,double yieldstrength,double limitstress,double elasticitymodulus);
    void insertdata(QString matiralname,double limitstress,double elasticitymodulus);
    void insertdata(QString matiralname,double yieldstrength,double limitstress,double elasticitymodulus);
    ~matiral();

signals:
private:
    QSqlDatabase *matiraldb;
    QDir *folder;
    QString connectionname = "matiraldb_name";

    //自定义单元格Type的类型，在创建单元格的item时使用
    enum CellType{ctName=1000,ctSex,ctBirth,ctNation,ctPartyM,ctScore};
    //各字段在表格中的列号
    enum FieldColNum{colName=0,colSex,colBirth,colNation,colScore,colPartyM};
    QLabel *labCellIndex; //状态栏上用于显示单元格的行号、列号
    QLabel *labCellType; //状态栏上用于显示单元格的type
    QLabel *labStudID; //状态栏上用于显示学号
    void createItemsARow(int rowNo,QString Name,QString Sex,QDate birth,QString Nation,bool isPM,int score) ; //为某一行创建 items

};

#endif // MATIRAL_H
