#include "signinwindow.h"
#include "ui_signinwindow.h"

signinwindow::signinwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signinwindow)
{
    ui->setupUi(this);
}

signinwindow::~signinwindow()
{
    delete ui;
}
