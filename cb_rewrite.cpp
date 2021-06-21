#include "cb_rewrite.h"
#include "ui_cb_rewrite.h"

cb_rewrite::cb_rewrite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cb_rewrite)
{
    ui->setupUi(this);
}

cb_rewrite::~cb_rewrite()
{
    delete ui;
}
void cb_rewrite::thisshow(int type, int SN){
    exptype = type;
    rSN = SN;
    this->show();
}

void cb_rewrite::on_pushButton_clicked()
{
    this->hide();
    emit mpshow(ui->lineEdit->text());
}
