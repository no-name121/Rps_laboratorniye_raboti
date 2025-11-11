#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sort.h"
#include "functions.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setLength_valueChanged(int length)
{
    ui->inputArray->setRowCount(length);
}


void MainWindow::on_sortButton_clicked()
{
    std::vector<int> arrayToSort;

    for (int i = 0; i < ui->setLength->value(); i++)
        arrayToSort.push_back((ui->inputArray->item(i, 0)->text()).toInt());

    ui->initialArrayOutput->setText(QString::fromStdString(vectorToStr(arrayToSort)));

    gnome_sort(arrayToSort);

    ui->sortedArrayOutput->setText(QString::fromStdString(vectorToStr(arrayToSort)));
}


void MainWindow::on_pushButton_clicked()
{
    baza();
}

