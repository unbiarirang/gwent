#include "Qcard.h"
#include <QLabel>
#include <vector>
#include <QPixmap>
#include <QPushButton>
#include "global.h"
#include "clabel.h"

QCard::QCard(QWidget *parent):
    QLabel(parent),
    parentWidget(parent),
    x_coordinate(0), y_coordinate(0)
{

}

void QCard::mousePressEvent(QMouseEvent *event)
{
    x_coordinate = event->x();
    y_coordinate = event->y();
}

void QCard::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX()-x_coordinate-parentWidget->geometry().x(),
         event->globalY()-y_coordinate-parentWidget->geometry().y());
}

