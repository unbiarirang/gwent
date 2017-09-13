#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include "user.h"
#include "game.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QString>
#include <vector>
#include <QPair>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void placeCard(LO, ID);
    void turnFinished();
    void scoreChanged();

    void selectCardMyLine(ID, LO);
    void selectCardEnemyLine(ID, LO);

private slots:
    void changeStackedWidget(QWidget* page);

    // for page_login
    void showLoginDialog();
    void on_button_login_clicked();
    void goToMenu(QString);

    // for page_setDeck
    void on_button_setDeck_back_clicked();
    void on_button_setDeck_save1_clicked();
    void on_butoon_setDeck_save2_clicked();
    void cardSelected(int);

    // for page_menu
    void on_button_menu_deck_clicked();
    void on_button_menu_1p_clicked();

    // for game
    void gameCardSelected(int);

    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

    void removeCardFromHand(int);
    void deployCardToLine(int, int);
    void drawCard(int count);
    void removeCard(int, int);
    void revoke(int, int);
    void changeRoundScore();

    // for user2
    void deployWeather(int cardID, int line);

    void update();

private:
    Ui::MainWindow *ui;
    loginDialog *loginDial;

    std::vector<int> deck, deck1, deck2;

    Game* game;
    int line;
    int timeCount;
    int cardID;

    // for user1
    std::vector<QPair<int,int>>* emptyDeckSpace;
    std::vector<QPair<int,int>> emptyLine1, emptyLine2, emptyLine3;

    // for user 2
    std::vector<QPair<int,int>>* emptyDeckSpace_2;
    std::vector<QPair<int,int>> emptyLine1_2, emptyLine2_2, emptyLine3_2;
};

QPair<int,int> gridPosition(QWidget * widget);

#endif // MAINWINDOW_H
