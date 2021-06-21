#include "mysocket620.h"

mysocket620::mysocket620(int socket, QObject *parent) : QTcpSocket(parent)
{
    sockDec = socket;
    connect(this,SIGNAL(readyRead()),this,SLOT(recieveddata()));
    connect(this,SIGNAL(disconnected()),this,SLOT(cdisconnected()));
}
void mysocket620::recieveddata(){
    //防止粘包处理,一边处理一边读取
    //定义表头是###，表尾是&&&，假定数据中没有#与&
    //6-20增添了握手部分
    //数据处理部分
    QString n;
    QString temp;
    if(shakehand){//握手部分
        QString machineID;
        if(mytime.elapsed()/1000>2){//如果握手信号返回来时间超过2秒，则判定不正常
            qDebug()<<"shakehand timeout";
            disconnectFromHost();
            //emit shakehandre(false,sockDec,"0");
            return;
        }
        while(bytesAvailable()>0){
            temp = read(1);
            if(temp == "#"){
                n += temp;
            }
            if(n.contains("###",Qt::CaseSensitive)&&!n.contains("&&&",Qt::CaseSensitive)){
                //后面的都是数据，直到&&&的出现
                if(temp == "#"){
                }else{
                   n += temp;
                }
            }
            if(n.contains("###",Qt::CaseSensitive)&&n.contains("&&&",Qt::CaseSensitive)){
                //发射信号
                qDebug()<<n;
                if(n.split(" ").at(1) != "12345"){//判定shakehand 的密码部分是否正确，获取对应的机器代码
                    qDebug()<<"shakehand password incorrect";
                    //emit shakehandre(false,sockDec,"0");
                    disconnectFromHost();
                    return;
                }else{
                   machineID = n.split(" ").at(2);
                }
                n.clear();
            }
            if(n.size()>50) n.clear();
        }
        shakehand = false;
        //emit shakehandre(true,sockDec,machineID);
        emit shakehandsuc(sockDec,machineID);
    }else{//一般接收数据
        while(bytesAvailable()>0){
            temp = read(1);
            if(temp == "#"){
                n += temp;
            }
            if(n.contains("###",Qt::CaseSensitive)&&!n.contains("&&&",Qt::CaseSensitive)){
                //后面的都是数据，直到&&&的出现
                if(temp == "#"){
                }else{
                   n += temp;
                }
            }
            if(n.contains("###",Qt::CaseSensitive)&&n.contains("&&&",Qt::CaseSensitive)){
                //发射信号
                qDebug()<<n;
                n.clear();
            }
            if(n.size()>50) n.clear();
        }
    }
}
void mysocket620::handshake(){
    write("shake hand");
    shakehand = true;
    mytime.restart();
}
void mysocket620::sentdata(int sockID,QString content){

    if(sockID == sockDec){
        write(content.toUtf8());
    }else{
        return;
    }
}
void mysocket620::cdisconnected(){
    emit disconnectsig(sockDec);
}
