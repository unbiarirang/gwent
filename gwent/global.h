#ifndef GLOBAL_H
#define GLOBAL_H

#include "Qcard.h"
#include "clabel.h"
#include "cardBase.h"
#include <QLabel>
#include <vector>
#include <QPixmap>
#include <map>

extern std::vector<CLabel*> g_cardImages;
extern std::vector<CLabel*> g_cardImagesSmall_1;
extern std::vector<CLabel*> g_cardImagesSmall_2;
extern std::vector<CLabel*> g_user1CardImages;
extern std::vector<CLabel*> g_user2CardImages;
extern std::vector<CardBase*> g_cardCollection;
extern std::vector<QPixmap> g_cardPixmap;
extern std::vector<QPixmap> g_cardPixmapSmall;

namespace Global {
    void init();
}

enum CARDNO {
    DAGON = 1,
    FOGLET,
    GEELS,
    CELAENOHARPY,
    WOODLANDSPIRIT,
    EARTHELEMENTAL,
    CRONEWEAVESS,
    CRONEWHISPESS,
    CRONEBREWESS,
    ARCHGRIFFIN,
    CARANTHIR,
    FRIGHTENER,
    UNSEENELDER,
    ARACHAS,
    VRANWARRIOR,
    ARACHASBEHEMOTH,
    WILDHUNTRIDER,
    HARPYEGG,
    RABIDWOLF,
    LESSEREARTHELEMENTAL,

    FIRSTLIGHT,
    BITINGFROST,
    IMPENETRABLEFOG,
    TORRENTIALRAIN,
    LACERATE,
    COMMANDERSHORN,
    BEKKERSTWISTEDMIRROR,
    GERALTIGNI,
    ROACH,
    THUNDERBOLTPOTION
};


extern std::map<CARDNO, std::string> g_cardNameMap;

#endif // GLOBAL_H
