#include "functions.h"
#include <string>
#include <vector>
#include <QtSql>
#include <QDebug>

using namespace std;

string vectorToStr(vector<int>& vec){
    string str;

    for (int num : vec)
        str += (to_string(num) + " ");

    return str;
}

// потом удалить
void printDatabases(){
    QSqlQuery query;
    query.exec("SELECT * FROM users");
    while (query.next()) {
        qInfo() << query.value(0).toString() << query.value(1).toString();
    }

    query.exec("SELECT * FROM arrays");
    while (query.next()) {
        qInfo() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }
}

void createDatabase(){
    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS users(username varchar(20) PRIMARY KEY, password varchar(30));");
    query.exec("INSERT INTO users(username, password) VALUES ('biba', '12345');");
    query.exec("INSERT INTO users(username, password) VALUES ('boba', 'paroll');");

    query.exec("CREATE TABLE IF NOT EXISTS arrays(username varchar(20), initial_array varchar(200), sorted_array varchar(200), UNIQUE (username, initial_array), FOREIGN KEY (username) REFERENCES users(username));");
    query.exec("INSERT INTO arrays(username, initial_array, sorted_array) VALUES ('biba', '5 4 3 2 1', '1 2 3 4 5');");

    printDatabases();
}

void connectDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lab3_database.sqlite");

    if (db.open())
        qInfo() << "База база";
    else
        qInfo() << "Антибаза";

    createDatabase();
}
