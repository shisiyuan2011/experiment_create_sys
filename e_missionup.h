#ifndef E_MISSIONUP_H
#define E_MISSIONUP_H

#include <QWidget>
#include "QDebug"
#include "dispatch.h"

namespace Ui {
class e_missionup;
}

class e_missionup : public QWidget
{
    Q_OBJECT
public slots:
    void thisshow(int type,int SN);
    void mpshow(QString ID);
signals:
    void showMainwindow();
public:
    explicit e_missionup(QWidget *parent = nullptr);
    ~e_missionup();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::e_missionup *ui;
    int exptype,eSN;
    dispatch *dip;
};

#endif // E_MISSIONUP_H
