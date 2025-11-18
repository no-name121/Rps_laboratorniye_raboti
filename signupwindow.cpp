#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QSql>
#include <QSqlQuery>

signupwindow::signupwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signupwindow)
{
    ui->setupUi(this);
}

signupwindow::~signupwindow()
{
    delete ui;
}

void signupwindow::on_buttonBox_accepted()
{
    QString username = ui->setUsername->text();
    QString password = ui->setPassword->text();

    QSqlQuery query("INSERT INTO users(username, password) VALUES ('" + username + "', '" + password + "');");
}

