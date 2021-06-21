#ifndef CB_REWRITE_H
#define CB_REWRITE_H

#include <QWidget>

namespace Ui {
class cb_rewrite;
}

class cb_rewrite : public QWidget
{
    Q_OBJECT

public:
    explicit cb_rewrite(QWidget *parent = nullptr);
    ~cb_rewrite();
signals:
    void mpshow(QString ID);
public slots:
    void thisshow(int type,int SN);

private slots:
    void on_pushButton_clicked();

private:
    Ui::cb_rewrite *ui;
    int exptype, rSN;
};

#endif // CB_REWRITE_H
