#ifndef CARD_BASE_GUI_HPP
#define CARD_BASE_GUI_HPP

#include "cards/card_base.h"
#include "cards/card_item.h"

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

public:
    static QSize SIZE_OF_CARD;

    enum Target {
        UNK = 0,
        SELF = 1,
        MONSTER = 2,
    };

    Card_base_gui(Card_base* card, QWidget* parent = nullptr) : QWidget(parent), card(card)
    {
//        lastParent = parent;
        resize(SIZE_OF_CARD);
        setAcceptDrops(true);
    }

    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        QImage image;

        QString folder = "../../data/cards/";
        QString fname = folder + QString::fromStdString(card->ID) + ".png";
        image.load(fname);
        if (image.isNull())
            image.load(folder + "DMO_NOT_FOUND.png");
        image = image.scaled(SIZE_OF_CARD); // resize

        Card_item* cardItem = dynamic_cast<Card_item*>(card);
        if (cardItem && !cardItem->activated)
            painter.setOpacity(0.5);

        painter.drawImage(0, 0, image);
    }


    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override
    {
        move(event->globalPos() - globalDragStartPosition + relativeDragStartPosition);
//        this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
    void mouseReleaseEvent(QMouseEvent* event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

//    void dropEvent(QDropEvent *event) override
//    {
//        std::cerr << "drop on " << card->cardName << "\n";

//    }


    Card_base* card;

protected:
    QPoint relativeDragStartPosition;
    QPoint globalDragStartPosition;
//    QObject* lastParent;

signals:
    void dropped(Card_base*, Target);

//public slots:
};



#endif // CARD_BASE_GUI_HPP
