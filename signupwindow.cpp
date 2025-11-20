#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QSql>
#include <QSqlQuery>
#include <QMessageBox>

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
    QSqlQuery query;
    QString username = ui->setUsername->text();
    QString password = ui->setPassword->text();
    QString repeatedPassword = ui->setPasswordRepeat->text();

    query.exec("SELECT username FROM users WHERE USERNAME = '" + username + "';");

    if (query.next()) {
        QMessageBox::critical(this, "Ошибка", "Такой пользователь уже существует.");
        return;
    }

    if (username.simplified().size() < 1) {
        QMessageBox::critical(this, "Ошибка", "Имя пользователя не может быть пустым.");
        return;
    }

    if (password != repeatedPassword) {
        QMessageBox::critical(this, "Ошибка", "Пароли не совпадают.");
        return;
    }

    query.exec("INSERT INTO users(username, password) VALUES ('" + username + "', '" + password + "');");
}

