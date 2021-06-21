#ifndef MYSOCKET620_H
#define MYSOCKET620_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QTime>

class mysocket620 : public QTcpSocket
{
    Q_OBJECT
public:
    explicit mysocket620(int socket,QObject *parent = nullptr);
    void handshake();
public slots:
    void sentdata(int sockID,QString content);

signals:
    void shakehandre(bool result,int socket,QString machineID);
    void shakehandsuc(int socket,QString machineID);
    void disconnectsig(int sockDec);
private:
    int sockDec;//作为连接的唯一标识符
    QTime mytime;
    bool shakehand = false;//握手链接的标识符
private slots:
    void recieveddata();
    void cdisconnected();
};

#endif // MYSOCKET620_H
