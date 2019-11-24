#ifndef HAND_AREA_HPP
#define HAND_AREA_HPP

#include <QGraphicsView>

#include <QPainter>
#include <iostream>
//#include "../../src/gui/ui_player_window.h"


class PlayArea : public QGraphicsView
{
    Q_OBJECT
public:
    PlayArea(QWidget* parent = nullptr) : QGraphicsView(parent) {
//        std::cerr << "PLAY AREA\n";
        resize(400,400);
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
//        painter.drawEllipse(QPointF(20,10), 10,10);

//        QImage image1;
//        image1.load("/home/gergo/dev/backstabber/data/cards/DMO_T_BG.png");
//        painter.drawImage(155, 130, image1);
        std::cerr << "paint\n";
    }
};

#endif // HAND_AREA_HPP
