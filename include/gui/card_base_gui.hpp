#ifndef CARD_BASE_GUI_HPP
#define CARD_BASE_GUI_HPP

#include "cards/card_base.h"

#include <QSize>
#include <QWidget>
#include <QDrag>
#include <QLabel>
#include <QMimeData>
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
            image.load("../../data/cards/DMO_TI_01.png");
        else
            image.load("../../data/cards/DMO_T_BG.png");
        image = image.scaled(SIZE_OF_CARD); // resize
        painter.drawImage(0, 0, image);
    }


    void mousePressEvent(QMouseEvent* event) override
    {
        if( event->buttons() & Qt::LeftButton)
        {
            position = pos();
            dragStart = event->globalPos();

            raise();
        }
    }
    void mouseMoveEvent(QMouseEvent* event) override
    {
        move(event->globalPos() - dragStart + position);
        this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
    void mouseReleaseEvent(QMouseEvent* event) override
    {
        QWidget* window = dynamic_cast<QWidget*>(parent());
        if (window)
        {
            Card_base_gui *child = dynamic_cast<Card_base_gui*>(window->childAt(this->pos() + event->pos()));
            if (child)
                std::cerr << "REL on " << child->card->cardName << "\n";
            else
                std::cerr << "no \n";
        }

        this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }

    void dropEvent(QDropEvent *event) override
    {
        std::cerr << "drop on " << card->cardName << "\n";

    }



    Card_base* card;

    QPoint position;
    QPoint dragStart;

signals:
    void clicked(QPoint);

//public slots:
};


#endif // CARD_BASE_GUI_HPP
