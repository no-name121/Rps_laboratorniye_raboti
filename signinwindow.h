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

private:
    Ui::signinwindow *ui;
};

#endif // SIGNINWINDOW_H
