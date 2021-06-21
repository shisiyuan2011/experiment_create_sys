#ifndef B_MISSION_H
#define B_MISSION_H

#include <QWidget>
#include "ca_exppara.h"
#include "cb_rewrite.h"

namespace Ui {
class b_mission;
}

class b_mission : public QWidget
{
    Q_OBJECT

public:
    explicit b_mission(QWidget *parent = nullptr);
    ~b_mission();
signals:
    void caexpshow(int type,int SN);
    void reshow(int type,int SN);
    void showMaindow();
    void bmpshow(QString ID);
public slots:
    void thisshow(int type,int SN);
    void showmaindow();
    void mpshow(QString ID);

private slots:
    void on_New_clicked();

    void on_renew_clicked();

private:
    Ui::b_mission *ui;
    int exptype,bSN;
    ca_exppara *caexp;
    cb_rewrite *cbr;
};

#endif // B_MISSION_H
