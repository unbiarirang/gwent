#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showLoginDialog();
    void changeStackedWidget();

private:
    Ui::MainWindow *ui;
    loginDialog *loginDial;
    QStackedWidget *stackedWidget;
};

#endif // MAINWINDOW_H
