#include "include/gui/player_window.hpp"
#include "ui_player_window.h"

#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <iostream>
#include <thread>


PlayerWindow::PlayerWindow(Player* player, QWidget *parent) : player(player), QMainWindow(parent), ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);

    // Set areas pointers
    QWidget* areas = findChild<QWidget*>("Areas");
    if (!areas)
        throw std::runtime_error("Areas widget not found");
    const QObjectList& child_objs = areas->children();
    for (auto& child : child_objs)
    {
        QFrame* frame = static_cast<QFrame*>(child);
        if (child->objectName() == "MonsterArea")
            monsterArea = frame;
        else if (child->objectName() == "ItemsArea")
            itemsArea = frame;
        else if (child->objectName() == "HandArea")
            handArea = frame;
    }
    if (!handArea || !monsterArea || !itemsArea)
        throw std::runtime_error("Some area not found!");

//    connect(this, &PlayerWindow::refresh, this, &PlayerWindow::stateChanged, Qt::ConnectionType::QueuedConnection);
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}


void PlayerWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    for (QFrame* frame : {handArea, itemsArea, monsterArea})
        painter.drawText(frame->pos().x()+10, frame->pos().y()+20, frame->objectName());
}

void PlayerWindow::mousePressEvent(QMouseEvent* event)
{
//    std::cerr << event->type() << std::endl;
}

void PlayerWindow::mouseMoveEvent(QMouseEvent* event)
{

}

void PlayerWindow::stateChanged()
{
    // Gui logic
//    std::cerr << std::this_thread::get_id() << "\n";
    objects.clear();

    // HACK
    QPoint handAreaPos      = QPoint( 20, 10);
    QPoint itemsAreaPos     = QPoint( 20, height() / 3. * 1 + 10);
    QPoint monsterAreaPos   = QPoint( 20, height() / 3. * 0 + 10);

    std::cerr << height() << "\n";

    const int X_DISTANCE = 50;
    for (auto& hand_card : player->cards_hand)
    {
        std::shared_ptr<QWidget> card(new Card_base_gui(hand_card, this));
        card->move(handAreaPos);
        objects.push_back(card);
        handAreaPos.setX(handAreaPos.x() + Card_base_gui::SIZE_OF_CARD.width() + X_DISTANCE);
    }
}
