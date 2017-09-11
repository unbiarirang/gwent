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

void Global::init() {
    // init g_cardNameMap
    g_cardNameMap[CARDNO::dagon] = "dagon";
    g_cardNameMap[CARDNO::foglet] = "foglet";
    g_cardNameMap[CARDNO::geels] = "geels";
    g_cardNameMap[CARDNO::celaenoharpy] = "celaenoHarpy";
    g_cardNameMap[CARDNO::woodlandSpirit] = "woodlandSpirit";
    g_cardNameMap[CARDNO::earthElemental] = "earthElemental";
    g_cardNameMap[CARDNO::croneWeavess] = "croneWeavess";
    g_cardNameMap[CARDNO::croneWhispess] = "croneWhispess";
    g_cardNameMap[CARDNO::croneBrewess] = "croneBrewess";
    g_cardNameMap[CARDNO::archgriffin] = "archgriffin";
    g_cardNameMap[CARDNO::caranthir] = "caranthir";
    g_cardNameMap[CARDNO::frightener] = "frightener";
    g_cardNameMap[CARDNO::unseenElder] = "unseenElder";
    g_cardNameMap[CARDNO::archas] = "arachas";
    g_cardNameMap[CARDNO::vranWarrior] = "vranWarrior";
    g_cardNameMap[CARDNO::arachasBehemoth] = "arachasBehemoth";
    g_cardNameMap[CARDNO::wildHuntRider] = "wildHuntRider";
    g_cardNameMap[CARDNO::harpyEgg] = "harpyEgg";
    g_cardNameMap[CARDNO::rabidWolf] = "rabidWolf";
    g_cardNameMap[CARDNO::lesserEarthElemental] = "lesserEarthElemental";

    g_cardNameMap[CARDNO::firstLight] = "firstLight";
    g_cardNameMap[CARDNO::bitingFrost] = "bitingFrost";
    g_cardNameMap[CARDNO::impenetrableFog] = "impenetrableFog";
    g_cardNameMap[CARDNO::torrentialRain] = "torrentialRain";
    g_cardNameMap[CARDNO::lacerate] = "lacerate";
    g_cardNameMap[CARDNO::commandersHorn] = "commandersHorn";
    g_cardNameMap[CARDNO::bekkersTwistedMirror] = "bekkersTwistedMirror";
    g_cardNameMap[CARDNO::geraltIgni] = "geraltIgni";
    g_cardNameMap[CARDNO::roach] = "roach";
    g_cardNameMap[CARDNO::thunderboltPotion] = "thunderboltPotion";


    // inti g_cardImages
    QPixmap image;
    CLabel* imageLabel[32];
    int i = 0;

    // load card images
    for (auto card : g_cardNameMap) {
        std::string name = card.second;
        image.load(":/images/images/card/" + QString::fromStdString(name) + ".png");
        imageLabel[i] = new CLabel();
        imageLabel[i]->setPixmap(image);
        imageLabel[i]->setScaledContents(true);
        g_cardImages.push_back(imageLabel[i]);
        i++;
    }
}
