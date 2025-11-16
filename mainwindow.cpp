#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sort.h"
#include "functions.h"
#include "signupwindow.h"
#include "signinwindow.h"
#include <vector>
#include <QInputDialog>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connectDatabase();
    ui->setupUi(this);

    // растягивание для строк таблицы
    ui->inputArray->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    // анимация для панельки
    panelAnimation = new QPropertyAnimation(ui->panel, "geometry");
    panelAnimation->setDuration(300);
    panelAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // чтобы часть виджетов задвигалась с панелькой
    moveProfileImage = new QPropertyAnimation(ui->profileImage, "pos");
    moveProfileImage->setDuration(300);
    moveProfileImage->setEasingCurve(QEasingCurve::InOutQuad);

    moveProfileName = new QPropertyAnimation(ui->profileName, "pos");
    moveProfileName->setDuration(300);
    moveProfileName->setEasingCurve(QEasingCurve::InOutQuad);

    moveSignInButton = new QPropertyAnimation(ui->signInButton, "pos");
    moveSignInButton->setDuration(300);
    moveSignInButton->setEasingCurve(QEasingCurve::InOutQuad);

    moveSignUpButton = new QPropertyAnimation(ui->signUpButton, "pos");
    moveSignUpButton->setDuration(300);
    moveSignUpButton->setEasingCurve(QEasingCurve::InOutQuad);

    // растягивание основных виджетов
    layoutAnimation = new QPropertyAnimation(ui->mainProgram, "geometry");
    layoutAnimation->setDuration(300);

    panelIsMaximized = true;

}

MainWindow::~MainWindow()
{
    // добавить удаление из базы массивов по юзерайди 0

    delete ui;
}

// изменение количества строк таблицы
void MainWindow::on_setLength_valueChanged(int length)
{
    ui->inputArray->setRowCount(length);
}

// сортировка массива и его вывод
void MainWindow::on_sortButton_clicked()
{
    std::vector<int> arrayToSort;

    for (int i = 0; i < ui->setLength->value(); i++)
        arrayToSort.push_back((ui->inputArray->item(i, 0)->text()).toInt());

    ui->initialArrayOutput->setText(QString::fromStdString(vectorToStr(arrayToSort)));

    gnome_sort(arrayToSort);

    ui->sortedArrayOutput->setText(QString::fromStdString(vectorToStr(arrayToSort)));
}

// заполнение случайными числами
void MainWindow::on_randomNumsButton_clicked()
{
    bool withRange = true;

    QString rangeFirstNum = QInputDialog::getText(this, "Ввод диапазона", "Введите первое число диапазона:\n(оставьте пустым для генерации без диапазона)", QLineEdit::Normal, "");
    QString rangeSecondNum = QInputDialog::getText(this, "Ввод диапазона", "Введите второе число диапазона:\n(оставьте пустым для генерации без диапазона)", QLineEdit::Normal, "");

    if (rangeFirstNum == "" || rangeSecondNum == "")
        withRange = false;

    int rangeSize = rangeSecondNum.toInt() - rangeFirstNum.toInt() + 1;

    for (int i = 0; i < ui->setLength->value(); i++){
        if (withRange)
            ui->inputArray->setItem(i, 0, new QTableWidgetItem(QString::number(rand() % rangeSize + rangeFirstNum.toInt())));
        else
            ui->inputArray->setItem(i, 0, new QTableWidgetItem(QString::number(rand())));
    }
}

// сохранение массивов
void MainWindow::on_saveButton_clicked()
{
    QSqlQuery query;

    QString initial_array = ui->initialArrayOutput->text();
    QString sorted_array = ui->sortedArrayOutput->text();

    query.exec("INSERT INTO arrays(user_id, initial_array, sorted_array) VALUES (0, '" + initial_array + "', '" + sorted_array + "');");

    printDatabases();
}

// скрытие виджетов
void MainWindow::animateWidgets(bool panelIsMaximized)
{
    int offset = 100;

    QPoint imgPos  = ui->profileImage->pos();
    QPoint namePos = ui->profileName->pos();
    QPoint inPos   = ui->signInButton->pos();
    QPoint upPos   = ui->signUpButton->pos();

    moveProfileImage->stop();
    moveProfileName->stop();
    moveSignInButton->stop();
    moveSignUpButton->stop();

    if (panelIsMaximized)
    {
        moveProfileImage->setStartValue(ui->profileImage->pos());
        moveProfileImage->setEndValue(QPoint(imgPos.x() - offset, imgPos.y()));
        moveProfileImage->start();

        moveProfileName->setStartValue(ui->profileName->pos());
        moveProfileName->setEndValue(QPoint(namePos.x() - offset, namePos.y()));
        moveProfileName->start();

        moveSignInButton->setStartValue(ui->signInButton->pos());
        moveSignInButton->setEndValue(QPoint(inPos.x() - offset, inPos.y()));
        moveSignInButton->start();

        moveSignUpButton->setStartValue(ui->signUpButton->pos());
        moveSignUpButton->setEndValue(QPoint(upPos.x() - offset, upPos.y()));
        moveSignUpButton->start();
    }
    else
    {
        moveProfileImage->setStartValue(ui->profileImage->pos());
        moveProfileImage->setEndValue(QPoint(imgPos.x() + offset, imgPos.y()));
        moveProfileImage->start();

        moveProfileName->setStartValue(ui->profileName->pos());
        moveProfileName->setEndValue(QPoint(namePos.x() + offset, namePos.y()));
        moveProfileName->start();

        moveSignInButton->setStartValue(ui->signInButton->pos());
        moveSignInButton->setEndValue(QPoint(inPos.x() + offset, inPos.y()));
        moveSignInButton->start();

        moveSignUpButton->setStartValue(ui->signUpButton->pos());
        moveSignUpButton->setEndValue(QPoint(upPos.x() + offset, upPos.y()));
        moveSignUpButton->start();
    }
}

// выдвижение панели
void MainWindow::on_menuButton_clicked()
{
    QRect panelStartGeometry = ui->panel->geometry();
    QRect panelEndGeometry = panelStartGeometry;

    QRect mainProgramStartGeometry = ui->mainProgram->geometry();
    QRect mainProgramEndGeometry = mainProgramStartGeometry;

    if (panelIsMaximized) {
        panelEndGeometry.setWidth(panelMinWidth);

        mainProgramEndGeometry.setX(panelMinWidth);
        mainProgramEndGeometry.setWidth(mainProgramStartGeometry.width() + (panelMaxWidth - panelMinWidth));
    }
    else {
        panelEndGeometry.setWidth(panelMaxWidth);

        mainProgramEndGeometry.setX(panelMaxWidth);
        mainProgramEndGeometry.setWidth(mainProgramStartGeometry.width() - (panelMaxWidth - panelMinWidth));
    }

    panelAnimation->setStartValue(panelStartGeometry);
    panelAnimation->setEndValue(panelEndGeometry);

    layoutAnimation->setStartValue(mainProgramStartGeometry);
    layoutAnimation->setEndValue(mainProgramEndGeometry);

    panelAnimation->start();
    layoutAnimation->start();

    animateWidgets(!panelIsMaximized);
    panelIsMaximized = !panelIsMaximized;
}

// регистрация
void MainWindow::on_signUpButton_clicked()
{
    signupwindow w;
    w.setModal(true);
    w.exec();
    //QSqlQuery query;

    //query.exec("INSERT INTO users(user_id, username, password) VALUES ()");
}

// вход
void MainWindow::on_signInButton_clicked()
{
    signinwindow w;
    w.setModal(true);
    w.exec();
}

