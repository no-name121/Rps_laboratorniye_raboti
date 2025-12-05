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

    static int arrayIndex;

public slots:
    void on_setLength_valueChanged(int length);

    void on_sortButton_clicked();

    void on_saveButton_clicked();

    void animateWidgets(bool panelIsMaximized);

    void on_menuButton_clicked();

    void on_randomNumsButton_clicked();

    void on_signUpButton_clicked();

    void on_signInButton_clicked();

    void setUsername(const QString& recievedUsername);

    void on_showSavedButton_clicked();

    void on_goLeftButton_clicked();

    void on_goRightButton_clicked();

    void on_infoButton_clicked();

public:
    Ui::MainWindow *ui;
private:
    QPropertyAnimation* panelAnimation;
    bool panelIsMaximized;
    int panelMinWidth = 60;
    int panelMaxWidth = 160;

    QPropertyAnimation* moveProfileImage;
    QPropertyAnimation* moveProfileName;
    QPropertyAnimation* moveSignInButton;
    QPropertyAnimation* moveSignUpButton;

    QPropertyAnimation *layoutAnimation;

    std::map <int, std::pair<QString, QString>> arrays;

    void showArray();
};
#endif // MAINWINDOW_H
