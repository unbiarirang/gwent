#ifndef PAGE_H
#define PAGE_H

#include <QStackedWidget>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include "game.h"

namespace PageSetDeck {
void init(QWidget* page);
}

namespace Page1P {
void startGame(QWidget* page, Game* game);
}

#endif // PAGE_H
