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
        qInfo() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }

    query.exec("SELECT * FROM arrays");
    while (query.next()) {
        qInfo() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }
}

void createDatabase(){
    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS users(user_id int PRIMARY KEY, username varchar(20), password varchar(30));");
    query.exec("INSERT INTO users(user_id, username, password) VALUES (1, 'biba', '12345');");
    query.exec("INSERT INTO users(user_id, username, password) VALUES (2, 'boba', 'paroll');");

    query.exec("CREATE TABLE IF NOT EXISTS arrays(user_id int, initial_array varchar(200), sorted_array varchar(200), UNIQUE (user_id, initial_array), FOREIGN KEY (user_id) REFERENCES users(user_id));");
    query.exec("INSERT INTO arrays(user_id, initial_array, sorted_array) VALUES (1, '5 4 3 2 1', '1 2 3 4 5');");

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
