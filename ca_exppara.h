#ifndef CA_EXPPARA_H
#define CA_EXPPARA_H

#include <QWidget>
#include "d_matiralinfo.h"

namespace Ui {
class ca_exppara;
}

class ca_exppara : public QWidget
{
    Q_OBJECT

public:
    explicit ca_exppara(QWidget *parent = nullptr);
    ~ca_exppara();
signals:
    void dmishow(int type, int SN,double po,int overcir);
    void showMainwindow();
    void campshow(QString ID);
public slots:
    void thisshow(int type,int SN);
    void showmainwindow();
    void mpshow(QString ID);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ca_exppara *ui;
    int exptype, caSN;
    d_matiralinfo *dm;
};

#endif // CA_EXPPARA_H
