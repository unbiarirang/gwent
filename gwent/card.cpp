#include "card.h"
#include <QLabel>

Card::Card(QWidget *parent):
    QLabel(parent),
    parentWidget(parent),
    x_coordinate(0), y_coordinate(0)
{

}

void Card::mousePressEvent(QMouseEvent *event)
{
    x_coordinate = event->x();
    y_coordinate = event->y();
}

void Card::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX()-x_coordinate-parentWidget->geometry().x(),
         event->globalY()-y_coordinate-parentWidget->geometry().y());
}
