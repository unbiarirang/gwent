#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include "page.h"
#include "global.h"
#include "cardBase.h"
#include "Qcard.h"
#include "enum.h"
#include <QTimer>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QLayout>
#include <QObjectList>
#include <QLayoutItem>
#include <vector>
#include <QTimer>
#include <QPair>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer::singleShot(100, this, SLOT(showLoginDialog()));

    util::init();
    Global::init();
    PageSetDeck::init(ui->page_setDeck);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStackedWidget(QWidget* page)
{
    ui->stackedWidget->setCurrentWidget(page);
}

/* for page_login */
void MainWindow::showLoginDialog()
{
    loginDial = new loginDialog(this);
    loginDial->show();

    connect(loginDial, SIGNAL(loginSuccess(QString)), this, SLOT(goToMenu(QString)));
}

void MainWindow::goToMenu(QString username)
{
    changeStackedWidget(ui->page_menu);
    ui->label_username->setText("hi, " + username);
}

void MainWindow::on_button_login_clicked()
{
    showLoginDialog();
}

/* for page_setDcek */
void MainWindow::cardSelected(int x)
{
    QVBoxLayout *vlayout = ui->vlayout_setDeck;

    QLabel *label = new QLabel();
    QString name = QString::fromStdString(g_cardNameMap[CARDNO(x)]);
    label->setText(name);

    vlayout->insertWidget(0, label);

    qDebug() << "click the card";

    deck.push_back(x);
}

void MainWindow::on_button_setDeck_back_clicked()
{
    int count = deck.size();
    deck.clear();

    QVBoxLayout *vlayout = ui->vlayout_setDeck;
    QLayoutItem *child;
    while (count) {
        child = vlayout->takeAt(0);
        delete child->widget();
        delete child;
        count--;
    }
    changeStackedWidget(ui->page_menu);
}

void MainWindow::on_button_setDeck_save1_clicked()
{
    int count = deck.size();
    deck1 = deck;
    deck.clear();

    QVBoxLayout *vlayout = ui->vlayout_setDeck;
    QLayoutItem *child;
    while (count) {
        child = vlayout->takeAt(0);
        delete child->widget();
        delete child;
        count--;
    }

    changeStackedWidget(ui->page_menu);
}

void MainWindow::on_butoon_setDeck_save2_clicked()
{
    int count = deck.size();
    deck2 = deck;
    deck.clear();

    QVBoxLayout *vlayout = ui->vlayout_setDeck;
    QLayoutItem *child;
    while (count) {
        child = vlayout->takeAt(0);
        delete child->widget();
        delete child;
        count--;
    }

    changeStackedWidget(ui->page_menu);
}

/* for page_menu */
void MainWindow::on_button_menu_deck_clicked()
{
    changeStackedWidget(ui->page_setDeck);
}

void MainWindow::on_button_menu_1p_clicked()
{
    changeStackedWidget(ui->page_1p);

    std::vector<CardBase*> defaultCollection = g_cardCollection; // TODO: default deck도 하나 만들어 놔야함
    std::vector<CardBase*> cardCollection1 = std::vector<CardBase*>();
    if (deck1 == std::vector<int>())    // didn't save deck
        cardCollection1 = defaultCollection; // default deck TODO: 카드 고르는 제한 만들기
    else {
        for (auto cardNo : deck1)
            cardCollection1.push_back(g_cardCollection[cardNo - 1]);
    }

    // cardCollection1 으로 user1을 만듬
    User* user1 = new User(&cardCollection1);
    User* user2 = new User(&defaultCollection);

//    connect(this, SIGNAL(placeCard(int,int)), this, SLOT(removeCardFromHand(int)));
//    connect(this, SIGNAL(placeCard(int,int)), this, SLOT(deployCardToLine(int,int)));
    connect(this, SIGNAL(placeCard(LO,ID)), user1, SLOT(deployCard(LO,ID)));
    connect(user1, SIGNAL(removeCardFromHandSignal(int)), this, SLOT(removeCardFromHand(int)));
    connect(user1, SIGNAL(deployCardToLineSignal(int,int)), this, SLOT(deployCardToLine(int,int)));
    connect(user1, SIGNAL(deployWeatherSignal(int,int)), this, SLOT(deployWeather(int,int)));
    connect(user1, SIGNAL(removeCardSignal(int,int)), this, SLOT(removeCard(int,int)));
    connect(user1, SIGNAL(scoreChanged()), this, SLOT(changeRoundScore()));
    connect(user1, SIGNAL(drawCardSignal(int)), this, SLOT(drawCard(int)));
    connect(this, SIGNAL(turnFinished()), user1, SLOT(myTurn()));

    //connect(this, SIGNAL(placeCard(LO,ID)), user2, SLOT(deployCard(LO,ID)));
    //connect(user2, SIGNAL(removeCardFromHandSignal(int)), this, SLOT(removeCardFromHand(int)));
    connect(user2, SIGNAL(deployCardToLineSignal(int,int)), this, SLOT(deployCardToLine(int,int)));
    connect(user2, SIGNAL(deployWeatherSignal(int,int)), this, SLOT(deployWeather(int,int)));
    connect(user2, SIGNAL(removeCardSignal(int,int)), this, SLOT(removeCard(int,int)));
    connect(user2, SIGNAL(scoreChanged()), this, SLOT(changeRoundScore()));
    //connect(user2, SIGNAL(drawCardSignal(int)), this, SLOT(drawCard(int)));
    //connect(this, SIGNAL(turnFinished()), user2, SLOT(myTurn()));


    emptyDeckSpace = new std::vector<QPair<int,int>>();
    emptyDeckSpace->push_back(qMakePair(7,2));
    emptyDeckSpace->push_back(qMakePair(7,3));
    emptyDeckSpace->push_back(qMakePair(7,4));
    emptyDeckSpace->push_back(qMakePair(7,5));
    emptyDeckSpace->push_back(qMakePair(7,6));
    emptyDeckSpace->push_back(qMakePair(7,7));
    emptyDeckSpace->push_back(qMakePair(7,8));
    emptyDeckSpace->push_back(qMakePair(6,2));
    emptyDeckSpace->push_back(qMakePair(6,3));
    emptyDeckSpace->push_back(qMakePair(6,4));
    emptyDeckSpace->push_back(qMakePair(6,5));
    emptyDeckSpace->push_back(qMakePair(6,6));
    emptyDeckSpace->push_back(qMakePair(6,7));
    emptyDeckSpace->push_back(qMakePair(6,8));
    emptyLine1.push_back(qMakePair(3,2));
    emptyLine1.push_back(qMakePair(3,3));
    emptyLine1.push_back(qMakePair(3,4));
    emptyLine1.push_back(qMakePair(3,5));
    emptyLine1.push_back(qMakePair(3,6));
    emptyLine2.push_back(qMakePair(4,2));
    emptyLine2.push_back(qMakePair(4,3));
    emptyLine2.push_back(qMakePair(4,4));
    emptyLine2.push_back(qMakePair(4,5));
    emptyLine2.push_back(qMakePair(4,6));
    emptyLine3.push_back(qMakePair(5,2));
    emptyLine3.push_back(qMakePair(5,3));
    emptyLine3.push_back(qMakePair(5,4));
    emptyLine3.push_back(qMakePair(5,5));
    emptyLine3.push_back(qMakePair(5,6));
    emptyLine1_2.push_back(qMakePair(2,2));
    emptyLine1_2.push_back(qMakePair(2,3));
    emptyLine1_2.push_back(qMakePair(2,4));
    emptyLine1_2.push_back(qMakePair(2,5));
    emptyLine1_2.push_back(qMakePair(2,6));
    emptyLine2_2.push_back(qMakePair(1,2));
    emptyLine2_2.push_back(qMakePair(1,3));
    emptyLine2_2.push_back(qMakePair(1,4));
    emptyLine2_2.push_back(qMakePair(1,5));
    emptyLine2_2.push_back(qMakePair(1,6));
    emptyLine3_2.push_back(qMakePair(0,2));
    emptyLine3_2.push_back(qMakePair(0,3));
    emptyLine3_2.push_back(qMakePair(0,4));
    emptyLine3_2.push_back(qMakePair(0,5));
    emptyLine3_2.push_back(qMakePair(0,6));

    game = new Game(user1, user2);
    Page1P::startGame(ui->page_1p, game);
}

void MainWindow::gameCardSelected(int id)
{
    qDebug() << "click the card cardID:" << id;
    cardID = id;

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//    timeCount = 0;
//    timer->start(1000);

    User* user = game->getUser(game->turn);
    std::vector<CLabel*> g_cardImagesSmall = std::vector<CLabel*>();
    if (user == game->getUser(0)) g_cardImagesSmall = g_cardImagesSmall_1;
    else g_cardImagesSmall = g_cardImagesSmall_2;

    Card* card = user->getCardFromID(cardID);
    if (card == nullptr) return;
    int no = user->getCardFromID(cardID)->no;
    QGridLayout *glayout = ui->glayout_page_1p;
    int index = glayout->indexOf(g_cardImagesSmall[no-1]);
    if (index == -1) return;
    auto pos = gridPosition(g_cardImagesSmall[no-1]);
    if (pos.first == 3 || pos.first == 4 || pos.first == 5) // select a card on my line
        emit selectCardMyLine(ID(cardID), LO(pos.first)); // ID/LO
    if (pos.first == 2 || pos.first == 1 || pos.first == 0)
        emit selectCardEnemyLine(ID(cardID), LO(5 - pos.first));
}
void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "line 1 clicked";
    emit placeCard(LO::LINE1, ID(cardID));
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "line 2 clicked";
    emit placeCard(LO::LINE2, ID(cardID));
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "line 3 clicked";
    emit placeCard(LO::LINE3, ID(cardID));
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "line 1 clicked";
    emit placeCard(LO::LINE1, ID(cardID));
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug() << "line 2 clicked";
    emit placeCard(LO::LINE2, ID(cardID));
}

void MainWindow::on_pushButton_6_clicked()
{
    qDebug() << "line 3 clicked";
    emit placeCard(LO::LINE3, ID(cardID));
}

void MainWindow::update()
{
    qDebug() << "timer update: " << timeCount;
    timeCount++;
}

QPair<int,int> gridPosition(QWidget * widget) {
  auto gp = qMakePair(-1,-1);
  if (! widget->parentWidget()) return gp;
  auto layout = widget->parentWidget()->findChild<QGridLayout*>("glayout_page_1p");
  if (! layout) return gp;
  int index = layout->indexOf(widget);
  Q_ASSERT(index >= 0);
  int rs,cs;
  layout->getItemPosition(index, &gp.first, &gp.second, &rs, &cs);
  return gp;
}

void MainWindow::removeCardFromHand(int cardID)
{
    User* user = game->getUser(game->turn);
    if (user == game->getUser(1)) return;   // user2 does not need to remove card(animation)

    Card* card = user->getCardFromID(cardID);
    if (card == nullptr) return;

    std::vector<CLabel*> g_cardImagesSmall = std::vector<CLabel*>();
    if (user == game->getUser(0)) g_cardImagesSmall = g_cardImagesSmall_1;
    else g_cardImagesSmall = g_cardImagesSmall_2;

    int no = card->no;
    QGridLayout *glayout = ui->glayout_page_1p;
    int index = glayout->indexOf(g_cardImagesSmall[no-1]);
    if (index == -1) return;


    auto pos = gridPosition(g_cardImagesSmall[no-1]);
    emptyDeckSpace->push_back(pos);
    // remove a card from deck 옮기는 거면 지울 필요가 없는듯?
    //glayout->takeAt(index)->widget();

//    deployCard(cardID, line);
}

void MainWindow::drawCard(int id)
{
    User* user = game->getUser(game->turn);
    if (user == game->getUser(1)) return;   // user2 does not need to draw card (animation)
    auto pos = (*emptyDeckSpace)[emptyDeckSpace->size()-1];
    emptyDeckSpace->pop_back();
    Card* card = user->getCardFromID(id);
    if (card == nullptr) return;
    int no = card->no;

    std::vector<CLabel*> g_cardImagesSmall = std::vector<CLabel*>();
    if (user == game->getUser(0)) g_cardImagesSmall = g_cardImagesSmall_1;
    else g_cardImagesSmall = g_cardImagesSmall_2;

    QGridLayout *glayout = ui->glayout_page_1p;
    glayout->addWidget(g_cardImagesSmall[no-1], pos.first, pos.second, 1, 1);
}

void MainWindow::deployCardToLine(int cardID, int line)
{
    qDebug() << "cardID: " << cardID;
    User* user = game->getUser(game->turn);
    Card* card = user->getCardFromID(cardID);
    if (card == nullptr) return;
    int no = user->getCardFromID(cardID)->no;
    QGridLayout *glayout = ui->glayout_page_1p;

    std::vector<QPair<int,int>>* emptyLine;
    if (user == game->getUser(0)) {
        if (line == 1) emptyLine = &emptyLine1;
        else if (line == 2) emptyLine = &emptyLine2;
        else if (line == 3) emptyLine = &emptyLine3;
        else return;
    } else if (user == game->getUser(1)){
        if (line == 1) emptyLine = &emptyLine1_2;
        else if (line == 2) emptyLine = &emptyLine2_2;
        else if (line == 3) emptyLine = &emptyLine3_2;
        else return;
    } else return;

    if (emptyLine->size() <= 0) {
        revoke(cardID, line);
        return;
    }

    //bool is_return = user->deployCard(LO(line+2), cardID);
//    if (is_return) { // user selected wrong line
//        revoke(cardID, line);
//        return;
//    }
    std::vector<CLabel*> g_cardImagesSmall = std::vector<CLabel*>();
    if (user == game->getUser(0)) g_cardImagesSmall = g_cardImagesSmall_1;
    else g_cardImagesSmall = g_cardImagesSmall_2;

    // insert a card into the line
    auto pos = (*emptyLine)[(*emptyLine).size()-1];
    (*emptyLine).pop_back();
    glayout->addWidget(g_cardImagesSmall[no-1], pos.first, pos.second, 1, 1);

    // insert a empty card into previous card location
    QPixmap pix = QPixmap();
    pix = pix.scaled(100, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    CLabel *emptyLabel = new CLabel();
    emptyLabel->setPixmap(pix);
    pos = (*emptyDeckSpace)[emptyDeckSpace->size()-1];
    glayout->addWidget(emptyLabel, pos.first, pos.second, 1, 1);

    emit turnFinished();
}

void MainWindow::deployWeather(int cardID, int line)
{
    qDebug() << "Weather cardID: " << cardID;
    User* user = game->getUser(game->turn);
    Card* card = user->getCardFromID(cardID);
    if (card == nullptr) { // weather card
        user = user->enemy;
        card = user->getCardFromID(cardID);
    }
    if (card == nullptr) return;
    int no = card->no;
    QGridLayout *glayout = ui->glayout_page_1p;

    std::vector<QPair<int,int>>* emptyLine;
    if (user == game->getUser(0)) { // 유저의 반대편 라인에 카드를 추가해줌
        if (line == 1) emptyLine = &emptyLine1_2;
        else if (line == 2) emptyLine = &emptyLine2_2;
        else if (line == 3) emptyLine = &emptyLine3_2;
        else return;
    } else if (user == game->getUser(1)){
        if (line == 1) emptyLine = &emptyLine1;
        else if (line == 2) emptyLine = &emptyLine2;
        else if (line == 3) emptyLine = &emptyLine3;
        else return;
    } else return;

    if (emptyLine->size() <= 0) {
        revoke(cardID, line);
        return;
    }

    std::vector<CLabel*> g_cardImagesSmall = std::vector<CLabel*>();
    if (user == game->getUser(0)) g_cardImagesSmall = g_cardImagesSmall_1;
    else g_cardImagesSmall = g_cardImagesSmall_2;

    // insert a card into the line
    auto pos = (*emptyLine)[(*emptyLine).size()-1];
    (*emptyLine).pop_back();
    glayout->addWidget(g_cardImagesSmall[no-1], pos.first, pos.second, 1, 1);

    // insert a empty card into previous card location
    QPixmap pix = QPixmap();
    pix = pix.scaled(100, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    CLabel *emptyLabel = new CLabel();
    emptyLabel->setPixmap(pix);
    pos = (*emptyDeckSpace)[emptyDeckSpace->size()-1];
    glayout->addWidget(emptyLabel, pos.first, pos.second, 1, 1);

    emit turnFinished();
}

void MainWindow::removeCard(int cardID, int line)
{
    //QThread::msleep(100);
    User* user = game->getUser(game->turn);
    Card* card = user->getCardFromID(cardID);
    if (card == nullptr) {
        user = user->enemy;
        card = user->getCardFromID(cardID);
    }
    if (card == nullptr) return;

    int no = card->no;
    QGridLayout *glayout = ui->glayout_page_1p;
    std::vector<CLabel*> g_cardImagesSmall = std::vector<CLabel*>();
    if (user == game->getUser(0)) g_cardImagesSmall = g_cardImagesSmall_1;
    else g_cardImagesSmall = g_cardImagesSmall_2;

    int index = glayout->indexOf(g_cardImagesSmall[no-1]);
    qDebug() << "(in remove card)index: " << index;
    if (index == -1) return;
    auto pos = gridPosition(g_cardImagesSmall[no-1]);

    std::vector<QPair<int,int>>* emptyLine;
    if (user == game->getUser(0)) {
        if (line == 1) emptyLine = &emptyLine1;
        else if (line == 2) emptyLine = &emptyLine2;
        else if (line == 3) emptyLine = &emptyLine3;
        else return;
    } else if (user == game->getUser(1)){
        if (line == 1) emptyLine = &emptyLine1_2;
        else if (line == 2) emptyLine = &emptyLine2_2;
        else if (line == 3) emptyLine = &emptyLine3_2;
        else return;
    } else return;

    (*emptyLine).push_back(qMakePair(pos.first,pos.second));
    delete glayout->takeAt(index)->widget();
}

void MainWindow::revoke(int cardID, int line)
{
    qDebug() << "emptyDeckSpace: " << (*emptyDeckSpace);
    auto pos = (*emptyDeckSpace)[emptyDeckSpace->size()-1];
    emptyDeckSpace->pop_back();
    qDebug() << "emptyDeckSpacke.pop_back(): " << pos.first<< ", " << pos.second;
    User* user = game->getUser(game->turn);
    Card* card = user->getCardFromID(cardID);
    if (card == nullptr) return;
    int no = card->no;

    std::vector<CLabel*> g_cardImagesSmall = std::vector<CLabel*>();
    if (user == game->getUser(0)) g_cardImagesSmall = g_cardImagesSmall_1;
    else g_cardImagesSmall = g_cardImagesSmall_2;

    QGridLayout *glayout = ui->glayout_page_1p;
    glayout->addWidget(g_cardImagesSmall[no-1], pos.first, pos.second, 1, 1);
}

void MainWindow::changeRoundScore()
{
    int score1 = game->getUser(0)->getRoundScore();
    int score2 = game->getUser(1)->getRoundScore();

    QLabel* scoreLabel1 = ui->label_totalScore1;
    QLabel* scoreLabel2 = ui->label_totalScore2;
    scoreLabel1->setText(QString::number(score1));
    scoreLabel2->setText(QString::number(score2));
}

