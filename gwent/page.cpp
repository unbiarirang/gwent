#include "page.h"
#include "global.h"
#include <QDebug>
#include <QSignalMapper>
#include <QSizePolicy>

std::map<ID, CLabel*> g_cardImagesSmall_1 = std::map<ID, CLabel*>();
std::map<ID, CLabel*> g_cardImagesSmall_2 = std::map<ID, CLabel*>();
extern std::vector<QPixmap> g_cardPixmapSmall;

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

     // insert empty cards into field
    QGridLayout *glayout = page->findChild<QGridLayout*>("glayout_page_1p");
    for (int i = 0; i < 10; i++) {
        QPixmap pix = QPixmap();
        pix = pix.scaled(100, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation);
        CLabel *emptyLabel = new CLabel();
        emptyLabel->setPixmap(pix);
        glayout->addWidget(emptyLabel, 7, i, 1, 1);
    }

    User* user1 = game->getUser(0);
    User* user2 = game->getUser(1);

    CLabel* imageLabelSmall[32];
    int i = 0;
    for (auto id : user1->deck) {
        imageLabelSmall[i] = new CLabel();
        Card* card = user1->getCardFromID(id);
        int no = card->no;
        imageLabelSmall[i]->setPixmap(g_cardPixmapSmall[no-1]);
        imageLabelSmall[i]->setScaledContents(true);
        QLabel *label = new QLabel(imageLabelSmall[i]);
        label->setText("  " + QString::number(card->strength));
        g_cardImagesSmall_1[id] = imageLabelSmall[i];
        QObject::connect(g_cardImagesSmall_1[id], SIGNAL(clicked()), m, SLOT(map()));
        m->setMapping(g_cardImagesSmall_1[id], id);
        i++;
    }

    CLabel* imageLabelSmall2[32];
    i = 0;
    for (auto id : user2->deck) {
        imageLabelSmall2[i] = new CLabel();
        Card* card = user2->getCardFromID(id);
        int no = user2->getCardFromID(id)->no;
        imageLabelSmall2[i]->setPixmap(g_cardPixmapSmall[no - 1]);
        imageLabelSmall2[i]->setScaledContents(true);
        QLabel *label = new QLabel(imageLabelSmall2[i]);
        label->setText("  " + QString::number(card->strength));
        g_cardImagesSmall_2[id] = imageLabelSmall2[i];
        QObject::connect(g_cardImagesSmall_2[id], SIGNAL(clicked()), m, SLOT(map()));
        m->setMapping(g_cardImagesSmall_2[id], id);
        i++;
    }

    user1->drawCard(10);
    user2->drawCard(10);

    QObject::connect(m, SIGNAL(mapped(int)), page->parent()->parent()->parent(), SLOT(gameCardSelected(int)));

    game->decideOrder();
    game->turnChange();
}
