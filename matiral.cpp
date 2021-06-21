#include "matiral.h"

matiral::matiral()
{
    folder = new QDir;
    matiraldb = new QSqlDatabase();
    createfolder();
    QString namedb = QString("D:/matiraldatabse/%1.%2").arg("matiraldatabase614").arg("db");
    *matiraldb = QSqlDatabase::addDatabase("QSQLITE",namedb);
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
"MATIRALNAME TEXT, YIELDSTRENGH TEXT, LIMITSTRESS TEXT, ELASTICITYMODULUS TEXT,ARASA TEXT,HARDNESS TEXT,"
"HEATTREAMENT TEXT);";
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"create table fail"<<query.lastError();
    }else{
        qDebug()<<"table create successful";
    }
    return;
}
para matiral::getinfo(int ID){
    struct para result;
    vector<QString> re;
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE ID=%1").arg(ID);
    QSqlQuery query(*matiraldb);
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
            result.arasa = query.value(5).toDouble();
            result.hard = query.value(6).toDouble();
            result.heattreament = query.value(7).toString();
        }else{
            qDebug()<<"end of the table";
        }
        return result;
    }
}
vector<QString> matiral::getinfovector(const int &ID){
    vector<QString> re;
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE ID=%1").arg(ID);
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return re;
    }else{
        if(query.next()){
            qDebug()<<"getdata data successful";
            re.push_back(QString::number(query.value(0).toInt()));
            re.push_back(query.value(1).toString());
            re.push_back(QString::number(query.value(2).toDouble()));
            re.push_back(QString::number(query.value(3).toDouble()));
            re.push_back(QString::number(query.value(4).toDouble()));
            re.push_back(query.value(5).toString()==""?"":QString::number(query.value(5).toDouble()));
            re.push_back(query.value(6).toString()==""?"":QString::number(query.value(6).toDouble()));
            re.push_back(query.value(7).toString());
        }else{
            qDebug()<<"end of the table";
        }
        return re;
    }
}
bool matiral::getinfobool(const int &ID){
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE ID = %1").arg(ID);
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return true;
    }else{
        return query.next();
    }
}
int matiral::getID(const QString &matiralname, const double &yieldstrength,
                   const double &limitstress, const double &elasticitym, const double &arasa, const double &hardness){
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE MATIRALNAME='%1' AND YIELDSTRENGH='%2'"
"AND LIMITSTRESS='%3' AND ELASTICITYMODULUS='%4' AND ARASA='%5' AND HARDNESS='%6'").
            arg(matiralname).
            arg(QString::number(yieldstrength)).
            arg(QString::number(limitstress)).
            arg(QString::number(elasticitym)).
            arg(arasa==0?"":QString::number(arasa)).
            arg(hardness==0?"":QString::number(hardness));
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return 0;
    }else{
        if(query.next()){
            qDebug()<<"getdata data successful";
            return query.value(0).toInt();
        }else{
            qDebug()<<"no exisit in table";
        }
    }
}
int matiral::getdataNUM(){
    QSqlQuery query(*matiraldb);
    query.exec("select * from MATIRALDB;");
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    while(model->canFetchMore()){
        model->fetchMore();
    }
    return model->rowCount();
}
bool matiral::getinfo(QString &matiralname,const double &yieldstrength,
                      const double &limitstress,const double &elasticitymodulus){
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE MATIRALNAME='%1' AND YIELDSTRENGH = '%2' AND "
                        "LIMITSTRESS='%3' AND ELASTICITYMODULUS='%4'").
                                                                arg(matiralname).
                                                                arg(yieldstrength).
                                                                arg(limitstress).
                                                                arg(elasticitymodulus);
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return true;
    }else{
        return query.next();
        qDebug()<<query.value(0);
    }
}
void matiral::insertdata(const QString &matiralname,const double &yieldstrength,
                         const double &limitstress,const double &elasticitymodulus){
    QString Qquery = QString("INSERT INTO MATIRALDB (MATIRALNAME,YIELDSTRENGH,LIMITSTRESS,ELASTICITYMODULUS) "
"VALUES('%1','%2','%3','%4')").
            arg(matiralname).
            arg(QString::number(yieldstrength)).
            arg(QString::number(limitstress)).
            arg(QString::number(elasticitymodulus));
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"insert data fail"<<query.lastError();
        return;
    }else{
        //qDebug()<<"insert data successful";
    }
}
void matiral::insertdata(const QString &matiralname,const double &limitstress,const double &elasticitymodulus){
    QString Qquery = QString("INSERT INTO MATIRALDB(MATIRALNAME,LIMITSTRESS,ELASTICITYMODULUS) "
            "VALUES('%1','%2','%3')").
            arg(matiralname).
            arg(QString::number(limitstress)).
            arg(QString::number(elasticitymodulus));
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"insert data fail"<<query.lastError();
        return;
    }else{
        //qDebug()<<"insert data successful";
    }
}

void matiral::insertdata(QString matiralname,double yieldstrength,double limitstress,double elasticitymodulus,
                double arasa,double hard,QString heattreament){
    QString Qquery = QString("INSERT INTO MATIRALDB(MATIRALNAME,YIELDSTRENGH,"
"LIMITSTRESS,ELASTICITYMODULUS,ARASA,HARDNESS,HEATTREAMENT) VALUES ('%1','%2','%3','%4','%5','%6','%7')").
            arg(matiralname).
            arg((yieldstrength==0?"":QString::number(yieldstrength))).
            arg(QString::number(limitstress)).
            arg(QString::number(elasticitymodulus)).
            arg((arasa==0?"":QString::number(arasa))).
            arg((hard==0?"":QString::number(hard))).
            arg((heattreament==""?"":heattreament));

    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"insert data fail"<<query.lastError();
        return;
    }else{
        qDebug()<<"insert data successful";
    }
}

bool matiral::getinfo(const QString &matiralname,const double &yieldstrength,const double &limitstress,
                      const double &elasticitym, const double &arasa, const double &hardness){
    QString Qquery = QString("SELECT * FROM MATIRALDB WHERE MATIRALNAME='%1' AND YIELDSTRENGH='%2'"
"AND LIMITSTRESS='%3' AND ELASTICITYMODULUS='%4' AND ARASA='%5' AND HARDNESS='%6'").
            arg(matiralname).
            arg(QString::number(yieldstrength)).
            arg(QString::number(limitstress)).
            arg(QString::number(elasticitym)).
            arg(arasa==0?"":QString::number(arasa)).
            arg(hardness==0?"":QString::number(hardness));
    QSqlQuery query(*matiraldb);
    if(!query.exec(Qquery)){
        qDebug()<<"getdata data fail"<<query.lastError();
        return true;
    }else{
        return query.next();
    }
}

