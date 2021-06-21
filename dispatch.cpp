#include "dispatch.h"
#include "ui_dispatch.h"

dispatch::dispatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dispatch)
{
    ui->setupUi(this);
    mm = new myserver620;
}

dispatch::~dispatch()
{
    delete ui;
}
