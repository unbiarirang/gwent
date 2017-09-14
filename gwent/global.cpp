#include "global.h"
#include "Qcard.h"
#include <QLabel>
#include <vector>
#include <QPixmap>
#include <QPushButton>
#include "clabel.h"
#include <string>

std::map<CARDNO, std::string> g_cardNameMap = std::map<CARDNO, std::string>();
std::vector<CLabel*> g_cardImages = std::vector<CLabel*>();

std::vector<CLabel*> g_user1CardImages = std::vector<CLabel*>();
std::vector<CLabel*> g_user2CardImages = std::vector<CLabel*>();
std::vector<QPixmap> g_cardPixmap = std::vector<QPixmap>();
std::vector<QPixmap> g_cardPixmapSmall = std::vector<QPixmap>();
std::vector<CardBase*> g_cardCollection = std::vector<CardBase*>();


void Global::init() {
    // init g_cardNameMap
    g_cardNameMap[CARDNO::DAGON] = "dagon";
    g_cardNameMap[CARDNO::FOGLET] = "foglet";
    g_cardNameMap[CARDNO::GEELS] = "geels";
    g_cardNameMap[CARDNO::CELAENOHARPY] = "celaenoHarpy";
    g_cardNameMap[CARDNO::WOODLANDSPIRIT] = "woodlandSpirit";
    g_cardNameMap[CARDNO::EARTHELEMENTAL] = "earthElemental";
    g_cardNameMap[CARDNO::CRONEWEAVESS] = "croneWeavess";
    g_cardNameMap[CARDNO::CRONEWHISPESS] = "croneWhispess";
    g_cardNameMap[CARDNO::CRONEBREWESS] = "croneBrewess";
    g_cardNameMap[CARDNO::ARCHGRIFFIN] = "archgriffin";
    g_cardNameMap[CARDNO::CARANTHIR] = "caranthir";
    g_cardNameMap[CARDNO::FRIGHTENER] = "frightener";
    g_cardNameMap[CARDNO::UNSEENELDER] = "unseenElder";
    g_cardNameMap[CARDNO::ARACHAS] = "arachas";
    g_cardNameMap[CARDNO::VRANWARRIOR] = "vranWarrior";
    g_cardNameMap[CARDNO::ARACHASBEHEMOTH] = "arachasBehemoth";
    g_cardNameMap[CARDNO::WILDHUNTRIDER] = "wildHuntRider";
    g_cardNameMap[CARDNO::HARPYEGG] = "harpyEgg";
    g_cardNameMap[CARDNO::RABIDWOLF] = "rabidWolf";
    g_cardNameMap[CARDNO::LESSEREARTHELEMENTAL] = "lesserEarthElemental";

    g_cardNameMap[CARDNO::FIRSTLIGHT] = "firstLight";
    g_cardNameMap[CARDNO::BITINGFROST] = "bitingFrost";
    g_cardNameMap[CARDNO::IMPENETRABLEFOG] = "impenetrableFog";
    g_cardNameMap[CARDNO::TORRENTIALRAIN] = "torrentialRain";
    g_cardNameMap[CARDNO::LACERATE] = "lacerate";
    g_cardNameMap[CARDNO::COMMANDERSHORN] = "commandersHorn";
    g_cardNameMap[CARDNO::BEKKERSTWISTEDMIRROR] = "bekkersTwistedMirror";
    g_cardNameMap[CARDNO::GERALTIGNI] = "geraltIgni";
    g_cardNameMap[CARDNO::ROACH] = "roach";
    g_cardNameMap[CARDNO::THUNDERBOLTPOTION] = "thunderboltPotion";

    // init cardInfo
    int figures[][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 2, 1, 1, 1, 4, 1, 0, 6, 3, 0, 41, 0, 0, 0, 0},
                           {0, 2, 0, 0, 0, 4, 2, 0, 4, 1, 0, 42, 0, 0, 0, 0},
                           {0, 2, 0, 0, 0, 4, 3, 0, 1, 3, 0, 43, 0, 0, 0, 0 },
                           {0, 2, 0, 0, 0, 4, 4, 0, 5, 1, 0, 44, 0, 0, 18, 0},
                           { 0, 2, 0, 0, 0, 4, 5, 0, 5, 3, 0, 45, 0, 23, 19, 0},
                           { 0, 2, 0, 0, 0, 1, 6, 0, 6, 1, 0, 46, 0, 1, 20, 0},
                           { 0, 2, 0, 0, 0, 3, 7, 0, 6, 2, 0, 47, 0, 8, 9, 0 },
                           {0, 2, 0, 0, 0, 3, 8, 0, 6, 2, 0, 47, 0, 7, 9, 0 },
                           { 0, 2, 0, 0, 0, 3, 9, 0, 8, 2, 0, 47, 0, 7, 8, 0 },
                           { 0, 2, 0, 0, 0, 4, 10, 0, 8, 1, 0, 50, 0, 0, 0, 0 },
                           { 0, 2, 0, 0, 0, 4, 11, 0, 8, 3, 0, 51, 0, 0, 22, 0},
                           {0, 2, 1, 0, 0, 4, 12, 0, 12, 2, 0, 52, 0, 0, 1, 0},
                           {0, 2, 1, 1, 1, 4, 13, 0, 5, 3, 53, 53, 0, 2, 0, 0},
                           { 0, 2, 0, 0, 0, 2, 14, 0, 3, 1, 0, 54, 0, 0, 14, 0 },
                           {0, 2, 0, 0, 0, 4, 15, 0, 6, 1, 0, 55, 0, 1, 0, 0},
                           {0, 2, 0, 0, 0, 3, 16, 0, 6, 1, 56, 4, 0, 1, 2, 0 },
                           { 0, 2, 0, 0, 0, 4, 17, 0, 8, 1, 0, 57, 0, 0, 22, 0},
                           {0, 2, 1, 0, 0, 4, 18, 0, 1, 1, 0, 0, 58, 0, 0, 4 },
                           { 0, 2, 1, 0, 0, 1, 19, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
                           { 0, 2, 1, 0, 0, 1, 20, 0, 2, 1, 0, 0, 0, 0, 0, 0 },
                           {0, 1, 1, 0, 0, 5, 21, 0, 0, 1, 0, 21, 0, 0, 1, 0},
                           { 0, 1, 0, 0, 0, 6, 22, 2, 0, 1, 22, 22, 0, 2, 2, 0},
                           { 0, 1, 0, 0, 0, 6, 23, 2, 0, 1, 23, 23, 0, 2, 2, 0},
                           {0, 1, 0, 0, 0, 6, 24, 1, 0, 1, 24, 24, 0, 1, 1, 0 },
                           { 0, 1, 0, 0, 0, 5, 25, 3, 0, 1, 0, 25, 0, 3, 3, 0 },
                           { 0, 1, 0, 0, 0, 5, 26, 0, 0, 2, 0, 26, 0, 4, 4, 0},
                           { 0, 1, 0, 0, 0, 5, 27, 0, 0, 2, 0, 27, 0, 0, 0, 0 },
                           {0, 1, 0, 0, 0, 4, 28, 0, 5, 3, 0, 28, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 4, 29, 0, 4, 2, 0, 0, 0, 0, 0, 0 },
                           { 0, 1, 0, 0, 0, 5, 30, 0, 0, 1, 0, 30, 0, 2, 3, 0}};

    for (auto card : g_cardNameMap) {
        int no = int(card.first);
        std::string name = card.second;

        CardBase* cardBase = new CardBase(name, figures[no][0], figures[no][1], figures[no][2], figures[no][3],
            figures[no][4], figures[no][5], figures[no][6], figures[no][7], figures[no][8], figures[no][9], figures[no][10], figures[no][11],
            figures[no][12], figures[no][13], figures[no][14], figures[no][15]);
        g_cardCollection.push_back(cardBase);
    }

    // inti g_cardImages
    QPixmap image[32];
    QPixmap imageSmall[32];
    CLabel* imageLabel[32];
    CLabel* imageLabelSmall[32];
    CLabel* imageLabelSmall_2[32];
    int i = 0;

    // load card images
    for (auto card : g_cardNameMap) {
        std::string name = card.second;
        image[i].load(":/images/images/card/" + QString::fromStdString(name) + ".png");
        imageSmall[i] = image[i].scaled(100, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation);
        g_cardPixmap.push_back(image[i]);
        g_cardPixmapSmall.push_back(imageSmall[i]);

        imageLabel[i] = new CLabel();
        imageLabel[i]->setPixmap(image[i]);
        imageLabel[i]->setScaledContents(true);
        g_cardImages.push_back(imageLabel[i]);

//        imageLabelSmall[i] = new CLabel();
//        imageLabelSmall[i]->setPixmap(imageSmall[i]);
//        imageLabelSmall[i]->setScaledContents(true);
//        g_cardImagesSmall_1.push_back(imageLabelSmall[i]);

//        imageLabelSmall_2[i] = new CLabel();
//        imageLabelSmall_2[i]->setPixmap(imageSmall[i]);
//        imageLabelSmall_2[i]->setScaledContents(true);
//        g_cardImagesSmall_2.push_back(imageLabelSmall_2[i]);
        i++;
    }
}
