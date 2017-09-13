#ifndef QCARD_H
#define QCARD_H

#include <QMouseEvent>
#include <QWidget>
#include <QLabel>

class QCard : public QLabel
{
    Q_OBJECT
public:
    explicit QCard(QWidget *parent = 0);

    // enable drag and drop cards
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    QWidget* parentWidget;
    int x_coordinate, y_coordinate;
};

#endif // QCARD_H
