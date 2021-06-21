#ifndef MYSERVERTHREAD620_H
#define MYSERVERTHREAD620_H

#include <QObject>
#include <QThread>
#include "myserver620.h"
#include "mysocket620.h"

class myserverthread620 : public QThread
{
    Q_OBJECT
public:
    explicit myserverthread620(int socket, QObject *parent = nullptr);
    ~myserverthread620();

signals:
    void stsentdata(int ID, QString content);
    void shakehandsuc(int sockDec,QString machineID);
    void tdisconnectedsig(int sockDec);
public slots:
    //void serthreadsentdata(int ID, QString content);
    void shakehandsucslot(int sockDec,QString machineID);
    void tdisconnectedslot(int sockDec);
    void sentdatast(int sockDec,QString content);
private:
    int sockDec;
    mysocket620 *mysocket;
private:
    void run();


};

#endif // MYSERVERTHREAD620_H
