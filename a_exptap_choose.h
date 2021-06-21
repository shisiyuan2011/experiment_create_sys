#ifndef A_EXPTAP_CHOOSE_H
#define A_EXPTAP_CHOOSE_H

#include <QWidget>
#include "b_mission.h"

namespace Ui {
class a_exptap_choose;
}

class a_exptap_choose : public QWidget
{
    Q_OBJECT

public:
    explicit a_exptap_choose(QWidget *parent = nullptr);
    ~a_exptap_choose();
signals:
    void bmshow(int type,int SN);
    void showMainwindow();
public slots:
    void thisshow(int type);
    void showmaindow();

private slots:
    void on_SN_clicked();

    void on_ebuselu1_clicked();

private:
    Ui::a_exptap_choose *ui;
    b_mission *bm;
    int exptype;
};

#endif // A_EXPTAP_CHOOSE_H
