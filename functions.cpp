#include "functions.h"
#include <string>
#include <vector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>

using namespace std;

string vectorToStr(vector<int>& vec){
    string str;

    for (int num : vec)
        str += (to_string(num) + " ");

    return str;
}

void baza(){
    qInfo() << "Подключение к базе";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("Lab3");
    db.setUserName("root");
    db.setPassword("475769000");

    if (db.open()) {
        qInfo() << "База база";
    }
    else {
        qInfo() << "Антибаза";
    }
}
