#ifndef MYSERVER620_H
#define MYSERVER620_H

#include <QObject>
#include <QTcpServer>
#include "myserverthread620.h"
#include <vector>
#include <unordered_map>
using namespace std;
typedef struct mechineID{
    int sockDec;
    int machineID;
}machineID ;
class myserver620 : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver620(QObject *parent = nullptr);
    void sentdata(int socDec,QString content);//只能往sockdecIDlist中有的项目发送数据
public:
    vector<machineID> sockDecIDlist;//这个里面保存了所有可以通讯的机器号和sockDec
public slots:
    void shakehandsucslots(int sockDec,QString machineID);
    void disconnected(int sockDec);

signals:
    void sentdataser(int socDec,QString content);
private:
    void incomingConnection(qintptr sockDesc);


};

#endif // MYSERVER620_H
