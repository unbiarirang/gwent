#include "page.h"
#include "Qcard.h"
#include "global.h"
#include <QDebug>
#include <QSignalMapper>

void PageSetDeck::init(QWidget* page) {
    QSignalMapper *m = new QSignalMapper();

    QGridLayout *layout = page->findChild<QGridLayout*>("glayout_setDeck");
    QVBoxLayout *vlayout = page->findChild<QVBoxLayout*>("vlayout_setDeck");

    int i = 0;
    for (auto image : g_cardImages) {
        // mapping signal
        QObject::connect(image, SIGNAL(clicked()), m, SLOT(map()));
        m->setMapping(image, i+1);

        // add image
        layout->addWidget(image, i / 6, i % 6);
        i++;
    }
    QObject::connect(m, SIGNAL(mapped(int)), page->parent()->parent()->parent(), SLOT(cardSelected(int)));

    return;
}

void Page1P::startGame(QWidget* page, Game* game) {
    QSignalMapper *m = new QSignalMapper();
    game->setCardsToDeck();

    User* user1 = game->getUser(0);
    User* user2 = game->getUser(1);

    QPixmap imageSmall[40];
    CLabel* imageLabelSmall[32];
    int i = 0;
    for (auto id : user1->deck) {
        imageLabelSmall[i] = new CLabel();
        Card* card = user1->getCardFromID(id);
        int no = card->no;
        imageLabelSmall[i]->setPixmap(g_cardPixmapSmall[no-1]);
        imageLabelSmall[i]->setScaledContents(true);
        g_cardImagesSmall_1.push_back(imageLabelSmall[i]);

        QObject::connect(g_cardImagesSmall_1[i], SIGNAL(clicked()), m, SLOT(map()));
        m->setMapping(g_cardImagesSmall_1[i], id);
        i++;
    }

    CLabel* imageLabelSmall2[32];
    i = 0;
    for (auto id : user2->deck) {
        imageLabelSmall2[i] = new CLabel();
        int no = user2->getCardFromID(id)->no;
        imageLabelSmall2[i]->setPixmap(g_cardPixmapSmall[no - 1]);
        imageLabelSmall2[i]->setScaledContents(true);
        g_cardImagesSmall_2.push_back(imageLabelSmall2[i]);

        QObject::connect(g_cardImagesSmall_2[i], SIGNAL(clicked()), m, SLOT(map()));
        m->setMapping(g_cardImagesSmall_2[i], id);
        i++;
    }

    user1->drawCard(10);
    user2->drawCard(10);

    game->turn = 1;
    user2->deployCard(LO::LINE1, user2->hand[0]);
    user2->deployCard(LO::LINE2, user2->hand[0]);
    user2->deployCard(LO::LINE2, user2->hand[0]);

//    QGridLayout *glayout = page->findChild<QGridLayout*>("glayout_page_1p");

//    int i = 1;
//    int x, y;
//    for (auto id : user1->hand) {
//        x = i / 8 + 6;
//        y = 9 - (i % 7);
//        if (y == 9) y = 2;
//        int no = user1->getCardFromID(id)->no;
//        glayout->addWidget(g_cardImagesSmall[no - 1], x, y, 1, 1);
//        g_cardImagesSmall[no - 1]->setParent(page);

//        // mapping signal
//        QObject::connect(g_cardImagesSmall[no - 1], SIGNAL(clicked()), m, SLOT(map()));
//        m->setMapping(g_cardImagesSmall[no - 1], id);
//        i++;
//    }
//    for (auto id : user1->deck) {
//        int no = user1->getCardFromID(id)->no;
//        QObject::connect(g_cardImagesSmall[no - 1], SIGNAL(clicked()), m, SLOT(map()));
//        m->setMapping(g_cardImagesSmall[no - 1], id);
//        i++;
//    }
    QObject::connect(m, SIGNAL(mapped(int)), page->parent()->parent()->parent(), SLOT(gameCardSelected(int)));

    game->decideOrder();
    game->turn = 0; // FIXME: 나중에 없엠
    //game->startGame(page); 없엘 계획
}
