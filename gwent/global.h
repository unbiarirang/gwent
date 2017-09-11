#ifndef GLOBAL_H
#define GLOBAL_H

#include "Qcard.h"
#include "clabel.h"
#include <QLabel>
#include <vector>
#include <QPixmap>
#include <map>

extern std::vector<CLabel*> g_cardImages;

namespace Global {
    void init();
}

enum CARDNO {
    dagon = 1,
    foglet,
    geels,
    celaenoharpy,
    woodlandSpirit,
    earthElemental,
    croneWeavess,
    croneWhispess,
    croneBrewess,
    archgriffin,
    caranthir,
    frightener,
    unseenElder,
    archas,
    vranWarrior,
    arachasBehemoth,
    wildHuntRider,
    harpyEgg,
    rabidWolf,
    lesserEarthElemental,

    firstLight,
    bitingFrost,
    impenetrableFog,
    torrentialRain,
    lacerate,
    commandersHorn,
    bekkersTwistedMirror,
    geraltIgni,
    roach,
    thunderboltPotion
};

extern std::map<CARDNO, std::string> g_cardNameMap;

#endif // GLOBAL_H
