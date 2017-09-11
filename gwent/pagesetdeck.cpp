#include "pagesetdeck.h"
#include "Qcard.h"
#include "global.h"
#include <QSignalMapper>

void Page::init(QWidget* page) {
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
