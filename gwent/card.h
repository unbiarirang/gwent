#ifndef CARD_H
#define CARD_H

#include <QMouseEvent>
#include <QWidget>
#include <QLabel>

class Card : public QLabel
{
    Q_OBJECT
public:
    explicit Card(QWidget *parent = 0);

    // enable drag and drop cards
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    QWidget* parentWidget;
    int x_coordinate, y_coordinate;
};

#endif // CARD_H
