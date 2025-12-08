#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sort.h"
#include "functions.h"
#include "signupwindow.h"
#include "signinwindow.h"
#include <vector>
#include <QInputDialog>
#include <QMessageBox>
#include <QtSql>

int MainWindow::arrayIndex = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connectDatabase("lab3_database.sqlite");
    ui->setupUi(this);

    // растягивание для строк таблицы
    ui->inputArray->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    // анимация для панельки
    panelAnimation = new QPropertyAnimation(ui->panel, "geometry");
    panelAnimation->setDuration(300);
    panelAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // сдвиг виджетов панели
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

    // сдвиг основных виджетов
    layoutAnimation = new QPropertyAnimation(ui->mainProgram, "geometry");
    layoutAnimation->setDuration(300);

    panelIsMaximized = true;

}

MainWindow::~MainWindow()
{
    QSqlQuery query("DELETE FROM arrays WHERE username = 'Unsigned User';");

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
    QTableWidgetItem* slotValue;
    int arrayItem;
    bool inputIsCorrect = true;

    for (int i = 0; i < ui->setLength->value(); i++) {
        slotValue = ui->inputArray->item(i, 0);

        if (!slotValue || slotValue->text().isEmpty()) {
            QMessageBox::critical(this, "Ошибка", "Некорректный ввод массива.");
            return;
        }
        arrayItem = slotValue->text().toInt(&inputIsCorrect);

        if (!inputIsCorrect) {
            QMessageBox::critical(this, "Ошибка", "Некорректный ввод массива.");
            return;
        }
        arrayToSort.push_back(arrayItem);
    }

    ui->initialArrayOutput->setText(QString::fromStdString(vectorToStr(arrayToSort)));

    gnome_sort(arrayToSort);

    ui->sortedArrayOutput->setText(QString::fromStdString(vectorToStr(arrayToSort)));
}

// заполнение случайными числами
void MainWindow::on_randomNumsButton_clicked()
{
    bool withRange = true;
    bool rangeIsCorrect = true;

    QString rangeFirstNum = QInputDialog::getText(this, "Ввод диапазона", "Введите первое число диапазона(от -2147483648 до 2147483647):\n(оставьте пустым для генерации без диапазона)", QLineEdit::Normal, "");

    if (rangeFirstNum.toLong(&rangeIsCorrect) < -2147483648 || rangeFirstNum.toLong(&rangeIsCorrect) > 2147483647) {
        QMessageBox::critical(this, "Ошибка", "Выход за пределы диапазона.");
        return;
    }

    if (!rangeIsCorrect && !rangeFirstNum.simplified().isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ввод диапазона.");
        return;
    }

    QString rangeSecondNum = QInputDialog::getText(this, "Ввод диапазона", "Введите второе число диапазона(от -2147483648 до 2147483647):\n(оставьте пустым для генерации без диапазона)", QLineEdit::Normal, "");

    if (rangeSecondNum.toLong(&rangeIsCorrect) < -2147483648 || rangeSecondNum.toLong(&rangeIsCorrect) > 2147483647) {
        QMessageBox::critical(this, "Ошибка", "Выход за пределы диапазона.");
        return;
    }

    if (!rangeIsCorrect && !rangeSecondNum.simplified().isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Некорректный ввод диапазона.");
        return;
    }

    if (rangeFirstNum.simplified().isEmpty() && rangeSecondNum.simplified().isEmpty())
        withRange = false;

    int rangeSize = rangeSecondNum.toInt(&rangeIsCorrect) - rangeFirstNum.toInt(&rangeIsCorrect) + 1;

    if (rangeFirstNum > rangeSecondNum){
        QMessageBox::critical(this, "Ошибка", "Первое число диапазона больше второго.");
        return;
    }

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

    QString username = ui->profileName->text();
    QString initial_array = ui->initialArrayOutput->text();
    QString sorted_array = ui->sortedArrayOutput->text();

    if (initial_array.isEmpty() || sorted_array.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при сохранении пустого массива.");
        return;
    }

    query.exec("INSERT INTO arrays(username, initial_array, sorted_array) VALUES ('" + username + "', '" + initial_array + "', '" + sorted_array + "');");

    QMessageBox::information(this, "Сохранение успешно", "Массив сохранен в базу данных.");
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

}

// отображение юзернейма при входе
void MainWindow::setUsername(const QString& recievedUsername){
    ui->profileName->setText(recievedUsername);
}

// вход
void MainWindow::on_signInButton_clicked()
{
    signinwindow w;
    w.setModal(true);

    QDialog::connect(&w, SIGNAL(userSignedIn(QString)), this, SLOT(setUsername(QString)));

    w.exec();
}

// отображение сохраненного массива
void MainWindow::showArray(){
    ui->showSavedArrays->setText("Массив №" + QString::number(arrayIndex) + "\n\n"
                                 "Исходный:\n" + arrays[arrayIndex].first + "\n\n"
                                 "Отсортированный:\n" + arrays[arrayIndex].second);
}

// загрузка сохраненных массивов
void MainWindow::on_showSavedButton_clicked()
{
    arrayIndex = 1;

    QSqlQuery query("SELECT initial_array, sorted_array FROM arrays WHERE username = '" + ui->profileName->text() + "';");
    arrays.clear();

    for (int i = 1; query.next(); i++) {
        arrays[i] = std::pair(query.value(0).toString(), query.value(1).toString());
    }

    if (arrays.empty())
        ui->showSavedArrays->setText("Сохраненные массивы не найдены");
    else
        showArray();
}

// предыдущий сохраненный массив
void MainWindow::on_goLeftButton_clicked()
{
    if (!arrays.empty() && arrayIndex > 1) {
        arrayIndex--;
        showArray();
    }
}

// следующий сохраненный массив
void MainWindow::on_goRightButton_clicked()
{
    if (!arrays.empty() && arrayIndex < arrays.rbegin()->first) {
        arrayIndex++;
        showArray();
    }
}

// информация о программе
void MainWindow::on_infoButton_clicked()
{
    QMessageBox::about(this, "О программе", "Программа для сортировки массивов алгоритмом \"Гномьей сортировки\".\n"
                                            "Работает с массивами размером от 1 до 99.\n"
                                            "Работает в диапазоне чисел от -2147483648 до 2147483647");
}

