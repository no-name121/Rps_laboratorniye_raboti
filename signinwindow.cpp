#include "signinwindow.h"
#include "ui_signinwindow.h"
#include <QSql>
#include <QSqlQuery>
#include <QMessageBox>

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

void signinwindow::on_buttonBox_accepted()
{
    QString inpUsername = ui->inputUsername->text();
    QString inpPassword = ui->inputPassword->text();

    QSqlQuery query;

    query.exec("SELECT username, password FROM users WHERE username = '" + inpUsername + "';");
    if (query.next()){
        if (query.value("password").toString() == inpPassword) {
            emit userSignedIn(inpUsername);
        }
        else
            QMessageBox::critical(this, "Ошибка", "Неверный пароль.");
    }
    else {
        QMessageBox::critical(this, "Ошибка", "Пользователь не найден.");
    }

}

