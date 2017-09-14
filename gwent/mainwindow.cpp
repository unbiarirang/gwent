#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include "page.h"
#include "global.h"
#include "cardBase.h"
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
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QEasingCurve>

extern std::map<ID, CLabel*> g_cardImagesSmall_1;
extern std::map<ID, CLabel*> g_cardImagesSmall_2;
extern std::vector<QPixmap> g_cardPixmapSmall;

std::vector<CLabel*> labels = std::vector<CLabel*>();

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
    ui->label_username->setText("   hi, " + username);
    ui->label_username->setStyleSheet("font: 15pt 'Cambria'; color: rgb(220, 220, 220);");

    // falling label animation
    QPropertyAnimation *animation;
    animation = new QPropertyAnimation(ui->label_username, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(0, 0, 100, 30));
    animation->setEndValue(QRect(0, 130, 100, 30));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MainWindow::on_button_login_clicked()
{
    showLoginDialog();
}

/* for page_setDcek */
void MainWindow::cardSelected(int x)
{
    QVBoxLayout *vlayout = ui->vlayout_setDeck;

    int type = g_cardCollection[x-1]->type;
    int count = 0;
    if (type == TYPE::GOLD || type == TYPE::SILVER) count = 1;
    else count = 3;

    for (auto id : deck) {
        if (id == x) count--;
        if (count == 0) return;
    }

    QLabel *label = new QLabel();
    QString name = QString::fromStdString(g_cardNameMap[CARDNO(x)]);
    label->setText(name);

    vlayout->insertWidget(0, label);
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
    std::vector<CardBase*> cardCollection2 = std::vector<CardBase*>();
    if (deck1 == std::vector<int>())    // didn't save deck
        cardCollection1 = defaultCollection; // default deck TODO: 카드 고르는 제한 만들기
    else {
        for (auto cardNo : deck1)
            cardCollection1.push_back(g_cardCollection[cardNo - 1]);
    }
    if (deck2 == std::vector<int>())    // didn't save deck
        cardCollection2 = defaultCollection; // default deck TODO: 카드 고르는 제한 만들기
    else {
        for (auto cardNo : deck2)
            cardCollection2.push_back(g_cardCollection[cardNo - 1]);
    }

    // cardCollection1 으로 user1을 만듬
    User* user1 = new User(&cardCollection1);
    User* user2 = new User(&cardCollection2);

//    connect(this, SIGNAL(placeCard(int,int)), this, SLOT(removeCardFromHand(int)));
//    connect(this, SIGNAL(placeCard(int,int)), this, SLOT(deployCardToLine(int,int)));
    connect(this, SIGNAL(placeCard(LO,ID)), user1, SLOT(deployCard(LO,ID)));
    connect(user1, SIGNAL(removeCardFromHandSignal(int)), this, SLOT(removeCardFromHand(int)));
    connect(user1, SIGNAL(deployCardToLineSignal(int,int)), this, SLOT(deployCardToLine(int,int)));
    connect(user1, SIGNAL(deployWeatherSignal(int,int)), this, SLOT(deployWeather(int,int)));
    connect(user1, SIGNAL(removeCardSignal(int,int)), this, SLOT(removeCard(int,int)));
    connect(user1, SIGNAL(scoreChanged()), this, SLOT(changeRoundScore()));
    connect(user1, SIGNAL(drawCardSignal(int)), this, SLOT(drawCard(int)));
    connect(user1, SIGNAL(spawnCardSignal(int,int)), this, SLOT(spawnCard(int,int)));
    connect(user1, SIGNAL(changeUnitScoreSignal(int)), this, SLOT(changeUnitScore(int)));
    connect(this, SIGNAL(turnFinished()), user1, SLOT(myTurn()));

    //connect(this, SIGNAL(placeCard(LO,ID)), user2, SLOT(deployCard(LO,ID)));
    //connect(user2, SIGNAL(removeCardFromHandSignal(int)), this, SLOT(removeCardFromHand(int)));
    connect(user2, SIGNAL(deployCardToLineSignal(int,int)), this, SLOT(deployCardToLine(int,int)));
    connect(user2, SIGNAL(deployWeatherSignal(int,int)), this, SLOT(deployWeather(int,int)));
    connect(user2, SIGNAL(removeCardSignal(int,int)), this, SLOT(removeCard(int,int)));
    connect(user2, SIGNAL(scoreChanged()), this, SLOT(changeRoundScore()));
    connect(user2, SIGNAL(spawnCardSignal(int,int)), this, SLOT(spawnCard(int,int)));
    connect(user2, SIGNAL(changeUnitScoreSignal(int)), this, SLOT(changeUnitScore(int)));
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

    connect(game, SIGNAL(finishGameSignal()), this, SLOT(finishGame()));
    connect(this, SIGNAL(turnChangedSignal()), game, SLOT(turnChange()));
    connect(game, SIGNAL(turnChangedSignal()), game, SLOT(turnChange()));
    connect(user1, SIGNAL(turnChangedSignal()), game, SLOT(turnChange()));

    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), game, SLOT(turnChange()));
    user1->timer = new QTimer(this);
    user1->timer->setSingleShot(true);
    connect(user1->timer, SIGNAL(timeout()), game, SLOT(turnChange()));

    Page1P::startGame(ui->page_1p, game);
}

void MainWindow::gameCardSelected(int id)
{
    cardID = id;

    User* user = game->getUser(game->turn);
    std::map<ID, CLabel*> cardImagesSmall = std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = g_cardImagesSmall_1;
    else cardImagesSmall = g_cardImagesSmall_2;

    Card* card = user->getCardFromID(cardID);
    if (card == nullptr) return;

    int no = card->no;
    QGridLayout *glayout = ui->glayout_page_1p;
    int index = glayout->indexOf(cardImagesSmall[cardID]);
    if (index == -1) return;

    auto pos = gridPosition(cardImagesSmall[cardID]);
    if (pos.first == 3 || pos.first == 4 || pos.first == 5) // select a card on my line
        emit selectCardMyLine(ID(cardID), LO(pos.first)); // ID/LO
    if (pos.first == 2 || pos.first == 1 || pos.first == 0)
        emit selectCardEnemyLine(ID(cardID), LO(5 - pos.first));
}
void MainWindow::on_pushButton_3_clicked()
{
    emit placeCard(LO::LINE1, ID(cardID));
    game->getUser(0)->timer->stop();
    timer->start(1000);
}

void MainWindow::on_pushButton_2_clicked()
{
    emit placeCard(LO::LINE2, ID(cardID));
    game->getUser(0)->timer->stop();
    timer->start(1000);
}

void MainWindow::on_pushButton_clicked()
{
    emit placeCard(LO::LINE3, ID(cardID));
    game->getUser(0)->timer->stop();
    timer->start(1000);
}

void MainWindow::on_pushButton_4_clicked()
{
    emit placeCard(LO::LINE1, ID(cardID));
    game->getUser(0)->timer->stop();
    timer->start(1000);
}

void MainWindow::on_pushButton_5_clicked()
{
    emit placeCard(LO::LINE2, ID(cardID));
    game->getUser(0)->timer->stop();
    timer->start(1000);
}

void MainWindow::on_pushButton_6_clicked()
{
    emit placeCard(LO::LINE3, ID(cardID));
    game->getUser(0)->timer->stop();
    timer->start(1000);
}

void MainWindow::update()
{
    qDebug() << "timer update: " << timeCount;
    timeCount++;
}

QPair<int,int> gridPosition(QWidget * widget) {
  auto gp = qMakePair(-1,-1);
  if (!widget->parentWidget()) return gp;

  auto layout = widget->parentWidget()->findChild<QGridLayout*>("glayout_page_1p");
  if (!layout) return gp;

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

    std::map<ID, CLabel*> cardImagesSmall = std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = g_cardImagesSmall_1;
    else cardImagesSmall = g_cardImagesSmall_2;

    int no = card->no;
    QGridLayout *glayout = ui->glayout_page_1p;
    int index = glayout->indexOf(cardImagesSmall[cardID]);
    if (index == -1) return;


    auto pos = gridPosition(cardImagesSmall[cardID]);
    emptyDeckSpace->push_back(pos);
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

    std::map<ID, CLabel*> cardImagesSmall = std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = g_cardImagesSmall_1;
    else cardImagesSmall = g_cardImagesSmall_2;

    QGridLayout *glayout = ui->glayout_page_1p;
    glayout->addWidget(cardImagesSmall[id], pos.first, pos.second, 1, 1);
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

    std::map<ID, CLabel*> cardImagesSmall = std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = g_cardImagesSmall_1;
    else cardImagesSmall = g_cardImagesSmall_2;

    // insert a card into the line
    auto pos = (*emptyLine)[(*emptyLine).size()-1];
    (*emptyLine).pop_back();
    glayout->addWidget(cardImagesSmall[cardID], pos.first, pos.second, 1, 1);

    // insert a empty card into previous card location
    QPixmap pix = QPixmap();
    pix = pix.scaled(100, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    CLabel *emptyLabel = new CLabel();
    emptyLabel->setPixmap(pix);
    pos = (*emptyDeckSpace)[emptyDeckSpace->size()-1];
    glayout->addWidget(emptyLabel, pos.first, pos.second, 1, 1);
}

void MainWindow::deployWeather(int cardID, int line)
{
    qDebug() << "Weather cardID: " << cardID;
    User* user = game->getUser(game->turn);
    Card* card = user->getCardFromID(cardID);
    std::map<ID, CLabel*> cardImagesSmall = std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = g_cardImagesSmall_1;
    else cardImagesSmall = g_cardImagesSmall_2;

    if (card == nullptr) { // enemy's weather card
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

    // insert a card into the line
    auto pos = (*emptyLine)[(*emptyLine).size()-1];
    (*emptyLine).pop_back();
    glayout->addWidget(cardImagesSmall[cardID], pos.first, pos.second, 1, 1);

    // insert a empty card into previous card location
    QPixmap pix = QPixmap();
    pix = pix.scaled(100, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    CLabel *emptyLabel = new CLabel();
    emptyLabel->setPixmap(pix);
    pos = (*emptyDeckSpace)[emptyDeckSpace->size()-1];
    glayout->addWidget(emptyLabel, pos.first, pos.second, 1, 1);
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
    std::map<ID, CLabel*>* cardImagesSmall = new std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = &g_cardImagesSmall_1;
    else cardImagesSmall = &g_cardImagesSmall_2;

    int index = glayout->indexOf((*cardImagesSmall)[cardID]);
    if (index == -1) return;
    auto pos = gridPosition((*cardImagesSmall)[cardID]);

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
    if (QLayoutItem *w = glayout->takeAt(index)) {
        delete w;
    }
    if ((*cardImagesSmall)[cardID])
        delete (*cardImagesSmall)[cardID];
}

void MainWindow::revoke(int cardID, int line)
{
    auto pos = (*emptyDeckSpace)[emptyDeckSpace->size()-1];
    emptyDeckSpace->pop_back();
    User* user = game->getUser(game->turn);

    std::map<ID, CLabel*> cardImagesSmall = std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = g_cardImagesSmall_1;
    else cardImagesSmall = g_cardImagesSmall_2;

    QGridLayout *glayout = ui->glayout_page_1p;
    glayout->addWidget(cardImagesSmall[cardID], pos.first, pos.second, 1, 1);
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

void MainWindow::changeUnitScore(int cardID)
{
    User* user = game->getUser(game->turn);
    std::map<ID, CLabel*> cardImagesSmall = std::map<ID, CLabel*>();
    cardImagesSmall = g_cardImagesSmall_1;

    if (cardImagesSmall[cardID] == nullptr) cardImagesSmall = g_cardImagesSmall_2;
    if (cardImagesSmall[cardID] == nullptr) return;
    if (user->getCardFromID(cardID) == nullptr) user = user->enemy;
    if (user->getCardFromID(cardID) == nullptr) return;

    QLabel *label = cardImagesSmall[cardID]->findChild<QLabel*>();
    label->setText(QString::number(user->getCardFromID(cardID)->getStrength()));
}

std::vector<QLabel*> scoreLabels = std::vector<QLabel*>();
void MainWindow::spawnCard(int no, int id)
{
    User* user = game->getUser(game->turn);
    std::map<ID, CLabel*>* cardImagesSmall = new std::map<ID, CLabel*>();
    if (user == game->getUser(0)) cardImagesSmall = &g_cardImagesSmall_1;
    else cardImagesSmall = &g_cardImagesSmall_2;

    CLabel* label = new CLabel();
    label->setPixmap(g_cardPixmapSmall[no-1]);
    label->setScaledContents(true);
    labels.push_back(label);
    (*cardImagesSmall)[id] = label;

    QLabel *scoreLabel = new QLabel((*cardImagesSmall)[id]);
    scoreLabel->setText("  " + QString::number(g_cardCollection[no-1]->strength));
    scoreLabels.push_back(scoreLabel);
}

void MainWindow::finishGame()
{
    QString str;
    if (game->winner == 0) str = QString::fromStdString("you");
    else if (game->winner == 1) str = QString::fromStdString("AI");
    else str = QString::fromStdString("both of you");

    // print game result
    QMessageBox::information(this, "The game is over", "the winner is " + str);
}
