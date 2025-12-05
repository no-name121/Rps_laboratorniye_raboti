#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QDialog>

namespace Ui {
class signinwindow;
}

class signinwindow : public QDialog
{
    Q_OBJECT

public:
    explicit signinwindow(QWidget *parent = nullptr);
    ~signinwindow();

private slots:
    void on_buttonBox_accepted();

public:
    Ui::signinwindow *ui;

signals:
    void userSignedIn(const QString&);
};

#endif // SIGNINWINDOW_H
