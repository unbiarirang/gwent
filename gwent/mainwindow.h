#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "logindialog.h"
#include <QString>

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
    void changeStackedWidget(QWidget* page);
    void goToMenu(QString);

    void on_button_login_clicked();
    void cardSelected(int);

    void on_button_setDeck_back_clicked();

    void on_button_setDeck_save_clicked();

    void on_button_menu_deck_clicked();

private:
    Ui::MainWindow *ui;
    loginDialog *loginDial;

    int x;
};

#endif // MAINWINDOW_H
