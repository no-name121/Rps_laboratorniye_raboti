#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <QString>

std::string vectorToStr(std::vector<int>& vec);

void connectDatabase(QString name);

void createDatabase();

#endif // FUNCTIONS_H
