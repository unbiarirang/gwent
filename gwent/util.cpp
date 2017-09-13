#include "util.h"
#include <QtGlobal>
#include <QTime>

static int id = 0;

void util::init()
{
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
}

int util::getID()
{
	id++;
	return id;
}

int util::getRandNumBetween(int x, int y)
{
    return qrand() % ((y + 1) - x) + x;
}
