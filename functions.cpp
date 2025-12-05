#include "functions.h"
#include <string>
#include <vector>
#include <QtSql>
#include <QString>

using namespace std;

string vectorToStr(vector<int>& vec){
    string str;

    for (int num : vec)
        str += (to_string(num) + " ");

    return str;
}

void createDatabase(){
    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS users(username varchar(20) PRIMARY KEY, password varchar(30));");

    query.exec("CREATE TABLE IF NOT EXISTS arrays(username varchar(20), "
                                                 "initial_array varchar(200), "
                                                 "sorted_array varchar(200), "
                                                 "UNIQUE (username, initial_array), "
                                                 "FOREIGN KEY (username) REFERENCES users(username));");
}

void connectDatabase(QString name){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);

    db.open();

    createDatabase();
}
