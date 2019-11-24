#ifndef CARD_BASE_GUI_HPP
#define CARD_BASE_GUI_HPP

#include "cards/card_base.h"

#include <QSize>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <iostream>


class Card_base_gui : public QWidget
{
    Q_OBJECT

    const QSize SIZE_OF_CARD = QSize(100, 200);
public:
    Card_base_gui(QWidget* parent = nullptr) : QWidget(parent) { resize(SIZE_OF_CARD); }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        QImage image;
        image.load("/home/gergo/dev/backstabber/data/cards/DMO_T_BG.png");
        image = image.scaled(SIZE_OF_CARD); // resize
        painter.drawImage(0, 0, image);
    }

    void mousePressEvent(QMouseEvent* event)
    {
        std::cerr << event->type() << std::endl;
    }

    Card_base* card;

signals:
    void clicked();

//public slots:
};


#endif // CARD_BASE_GUI_HPP
