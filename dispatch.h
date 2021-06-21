#ifndef DISPATCH_H
#define DISPATCH_H

#include <QWidget>
#include "QThread"

namespace Ui {
class dispatch;
}

class dispatch : public QWidget
{
    Q_OBJECT

public:
    explicit dispatch(QWidget *parent = nullptr);
    ~dispatch();
signals:
    void tcpstart();
private:
    Ui::dispatch *ui;
    tcpip *tcplinks;
};

#endif // DISPATCH_H
