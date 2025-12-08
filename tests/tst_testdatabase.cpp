#include <QCoreApplication>
#include <QtTest>
#include <QtWidgets>
#include <vector>
#include <QSql>
#include <QSqlQuery>
#include "mainwindow.h"
#include "signupwindow.h"
#include "signinwindow.h"
#include "ui_signupwindow.h"
#include "ui_signupwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"

class TestDatabase : public QObject
{
    Q_OBJECT

public:
    TestDatabase();
    ~TestDatabase();

private:
    static std::unique_ptr<QTimer> createDialogAutoCloser();
    void runArrayTest(int dbSize);

private slots:
    void test100ArraysDB();
    void test1000ArraysDB();
    void test10000ArraysDB();
};

TestDatabase::TestDatabase() {}

TestDatabase::~TestDatabase() {}

void TestDatabase::test100ArraysDB() {
    QElapsedTimer testTimer;
    testTimer.start();

    srand(time(0));

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    MainWindow w;
    w.show();

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    connectDatabase("100ArraysDB.sqlite");

    // Добавление массивов
    auto closer = createDialogAutoCloser();
    int addedCount = 0;

    for (size_t i = 0; i < 100; i++) {
        w.ui->setLength->setValue(2 + rand() % 98);

        w.on_randomNumsButton_clicked();
        QCoreApplication::processEvents();

        w.on_sortButton_clicked();

        w.on_saveButton_clicked();
        QCoreApplication::processEvents();
        addedCount++;
    }

    qInfo() << "Добавление 100 массивов: " << testTimer.elapsed() << "мс";
    qInfo() << (addedCount == 100 ? "УСПЕШНО" : "НЕУДАЧА") ;

    // Выгрузка случайных 100
    runArrayTest(100);

    // Очистка
    QElapsedTimer delTimer;
    delTimer.start();

    QSqlQuery query;
    bool deleteArrays = query.exec("DELETE FROM arrays;");

    qInfo() << "Очистка базы данных на 100 массивов: " << delTimer.elapsed() << "мс";
    qInfo() << (deleteArrays ? "УСПЕШНО" : "НЕУДАЧА") ;
}

void TestDatabase::test1000ArraysDB() {
    QElapsedTimer testTimer;
    testTimer.start();

    srand(time(0));

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    MainWindow w;
    w.show();

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    connectDatabase("1000ArraysDB.sqlite");

    // Добавление массивов
    auto closer = createDialogAutoCloser();
    int addedCount = 0;

    for (size_t i = 0; i < 1000; i++) {
        w.ui->setLength->setValue(2 + rand() % 98);

        w.on_randomNumsButton_clicked();
        QCoreApplication::processEvents();

        w.on_sortButton_clicked();

        w.on_saveButton_clicked();
        QCoreApplication::processEvents();
        addedCount++;
    }

    qInfo() << "Добавление 1000 массивов: " << testTimer.elapsed() << "мс";
    qInfo() << (addedCount == 1000 ? "УСПЕШНО" : "НЕУДАЧА") ;

    // Выгрузка случайных 100
    runArrayTest(1000);

    // Очистка
    QElapsedTimer delTimer;
    delTimer.start();

    QSqlQuery query;
    bool deleteArrays = query.exec("DELETE FROM arrays;");

    qInfo() << "Очистка базы данных на 1000 массивов: " << delTimer.elapsed() << "мс";
    qInfo() << (deleteArrays ? "УСПЕШНО" : "НЕУДАЧА") ;
}

void TestDatabase::test10000ArraysDB() {
    QElapsedTimer testTimer;
    testTimer.start();

    srand(time(0));

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    MainWindow w;
    w.show();

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    connectDatabase("10000ArraysDB.sqlite");

    // Добавление массивов
    auto closer = createDialogAutoCloser();
    int addedCount = 0;

    for (size_t i = 0; i < 10000; i++) {
        w.ui->setLength->setValue(2 + rand() % 98);

        w.on_randomNumsButton_clicked();
        QCoreApplication::processEvents();

        w.on_sortButton_clicked();

        w.on_saveButton_clicked();
        QCoreApplication::processEvents();
        addedCount++;
    }

    qInfo() << "Добавление 10000 массивов: " << testTimer.elapsed() << "мс";
    qInfo() << (addedCount == 10000 ? "УСПЕШНО" : "НЕУДАЧА") ;

    // Выгрузка случайных 100
    runArrayTest(10000);

    // Очистка
    QElapsedTimer delTimer;
    delTimer.start();

    QSqlQuery query;
    bool deleteArrays = query.exec("DELETE FROM arrays;");

    qInfo() << "Очистка базы данных на 10000 массивов: " << delTimer.elapsed() << "мс";
    qInfo() << (deleteArrays ? "УСПЕШНО" : "НЕУДАЧА") ;
}

void TestDatabase::runArrayTest(int dbSize) {

    QElapsedTimer timer;
    timer.start();

    std::vector<int> indices;
    for (int i = 0; i < 100; i++) {
        indices.push_back(rand() % dbSize);
    }

    int successful = 0;
    for (int idx : indices) {
        QSqlQuery query;
        query.prepare("SELECT initial_array FROM arrays "
                      "WHERE username = 'Unsigned User' "
                      "LIMIT 1 OFFSET ?;");
        query.addBindValue(idx);
        if (query.exec() && query.next()) {
            successful++;
        }
    }

    qInfo() << "Среднее время работы с 1 массивом для БД на " << dbSize << ": "
            << timer.elapsed() / 100.0 << "мс";

    qInfo() << (successful == 100 ? "УСПЕШНО" : "НЕУДАЧА") ;
}

std::unique_ptr<QTimer> TestDatabase::createDialogAutoCloser() {
    auto timer = std::make_unique<QTimer>();
    timer->setInterval(1);
    timer->setSingleShot(false);

    QObject::connect(timer.get(), &QTimer::timeout, []() {
        QWidgetList widgets = QApplication::topLevelWidgets();
        for (QWidget* widget : widgets) {
            if (QDialog* dialog = qobject_cast<QDialog*>(widget)) {
                if (dialog->isVisible()) {
                    dialog->accept();
                    QCoreApplication::processEvents();
                }
            }
        }
    });

    timer->start();
    return timer;
}

QTEST_MAIN(TestDatabase)

#include "tst_testdatabase.moc"
