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
    Card_base_gui(QWidget* parent = nullptr) : QWidget(parent)
    {
        resize(SIZE_OF_CARD);
        setAcceptDrops(true);
    }

    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        QImage image;
        if (card->cardName == "alma")
            image.load("/home/gergo/dev/backstabber/data/cards/DMO_TI_01.png");
        else
            image.load("/home/gergo/dev/backstabber/data/cards/DMO_T_BG.png");
        image = image.scaled(SIZE_OF_CARD); // resize
        painter.drawImage(0, 0, image);
    }


    void mousePressEvent(QMouseEvent* event) override
    {
        if( event->buttons() & Qt::LeftButton)
        {
            position = pos();
            dragStart = event->globalPos();
        }
    }
    void mouseMoveEvent(QMouseEvent* event) override
    {
//        move(event->globalPos() - dragStart + position);
    }
    void mouseReleaseEvent(QMouseEvent* event) override
    {
        std::cerr << "REL on " << card->cardName << "\n";
//        parent()->asdasd();
//        event->
//        parent->mouseReleaseEvent(event);
        emit clicked(event->globalPos());
    }




    Card_base* card;

    QPoint position;
    QPoint dragStart;

signals:
    void clicked(QPoint);

//public slots:
};


#endif // CARD_BASE_GUI_HPP
