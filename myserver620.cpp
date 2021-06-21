#include "myserver620.h"

myserver620::myserver620(QObject *parent) : QTcpServer(parent)
{

}
void myserver620::incomingConnection(qintptr sockDesc){
    qDebug()<<"new connection"<<"sockDesc:"<<sockDesc;
    myserverthread620 *mythread = new myserverthread620(sockDesc);
    mythread->start();
    //connect(this,&myserver620::serversentdata,mythread,&myserverthread620::serthreadsentdata);
    connect(mythread,&myserverthread620::shakehandsuc,this,&myserver620::shakehandsucslots);
    connect(mythread,&myserverthread620::tdisconnectedsig,this,&myserver620::disconnected);
    connect(this,&myserver620::sentdataser,mythread,&myserverthread620::sentdatast);
}
void myserver620::shakehandsucslots(int sockDec,QString mID){
    machineID a = {sockDec,mID.toInt()};
    sockDecIDlist.push_back(a);
}
void myserver620::disconnected(int sockDec){
    //把vector中的内容删除
    auto it  = sockDecIDlist.begin();
    while(it != sockDecIDlist.end()){
        if(sockDec == it->sockDec){
            sockDecIDlist.erase(it,it+1);
            return;
        }
    }
}
void myserver620::sentdata(int socDec,QString content){
    bool exist = false;
    auto it  = sockDecIDlist.begin();
    while(it != sockDecIDlist.end()){
        if(socDec == it->sockDec){
            exist = true;
            break;
        }else{
            ++it;
        }
    }
    if(!exist){
        qDebug()<<"cannot sentdata to the socket which not contain in sockDecIDlist";
        return;
    }
    emit sentdataser(socDec,content);
}
