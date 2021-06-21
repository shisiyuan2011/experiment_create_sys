#ifndef D_MATIRALINFO_H
#define D_MATIRALINFO_H

#include <QWidget>
#include "matiral.h"
#include "e_missionup.h"
#include <QMessageBox>

namespace Ui {
class d_matiralinfo;
}

class d_matiralinfo : public QWidget
{
    Q_OBJECT

public:
    explicit d_matiralinfo(QWidget *parent = nullptr);
    ~d_matiralinfo();
signals:
    void emshow(int type, int SN);
    void showMainwindow();
    void dmpshow(QString ID);
public slots:
    void thisshow(int type,int SN,double po,int overcir);
    void showmainwindow();
    void mpshow(QString ID);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::d_matiralinfo *ui;
    double conf;
    int dovercir;
    int exptype,dSN;
    e_missionup *emu;
    matiral *mdb;
private:
    void refreshtable();
};

#endif // D_MATIRALINFO_H
