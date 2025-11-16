#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_setLength_valueChanged(int length);

    void on_sortButton_clicked();

    void on_saveButton_clicked();

    void animateWidgets(bool panelIsMaximized);

    void on_menuButton_clicked();

    void on_randomNumsButton_clicked();

    void on_signUpButton_clicked();

    void on_signInButton_clicked();

private:
    Ui::MainWindow *ui;

    QPropertyAnimation* panelAnimation;
    bool panelIsMaximized;
    int panelMinWidth = 60;
    int panelMaxWidth = 160;

    QPropertyAnimation* moveProfileImage;
    QPropertyAnimation* moveProfileName;
    QPropertyAnimation* moveSignInButton;
    QPropertyAnimation* moveSignUpButton;

    QPropertyAnimation *layoutAnimation;

};
#endif // MAINWINDOW_H
