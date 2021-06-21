#include "myserverthread620.h"

myserverthread620::myserverthread620(int socket, QObject *parent) : QThread(parent)
{
    sockDec = socket;
}
myserverthread620::~myserverthread620(){
    mysocket->close();
}
void myserverthread620::run(){
    mysocket = new mysocket620(sockDec);
    if(!mysocket->setSocketDescriptor(sockDec)){
        return;
    }
    qDebug()<<"successful connect";
    mysocket->handshake();
    //connect(this,&myserverthread620::stsentdata,mysocket,&mysocket620::sentdata);
    connect(mysocket,&mysocket620::shakehandsuc,this,&myserverthread620::shakehandsucslot);
    connect(mysocket,&mysocket620::disconnectsig,this,&myserverthread620::tdisconnectedslot);
    connect(this,&myserverthread620::stsentdata,mysocket,&mysocket620::sentdata);
    this->exec();
}/*
void myserverthread620::serthreadsentdata(int ID, QString content){
    emit stsentdata(ID,content);
}*/
void myserverthread620::shakehandsucslot(int sockDec,QString machineID){
    emit  shakehandsuc(sockDec,machineID);
}
void myserverthread620::tdisconnectedslot(int sockDec){
    this->quit();
    emit tdisconnectedsig(sockDec);
}
void myserverthread620::sentdatast(int sockDec,QString content){
    emit stsentdata(sockDec,content);
}
