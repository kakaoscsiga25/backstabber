#include "include/gui/player_window.hpp"
#include "ui_player_window.h"

#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <iostream>
#include <thread>


PlayerWindow::PlayerWindow(GameControll* gc, QWidget *parent) : QMainWindow(parent), ui(new Ui::PlayerWindow)
{
    player = gc->state.player;

    connect(gc, &GameControll::fightStarted, this, &PlayerWindow::fightStarted, Qt::ConnectionType::DirectConnection);
    connect(gc, &GameControll::fightEnded, this, &PlayerWindow::fightEnded, Qt::ConnectionType::DirectConnection);

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

//    connect(player, &Player::playCard_sign, this, &PlayerWindow::stateChanged);
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

    // Fight monster visualization
    if (fight)
    {
        std::string monsterName = fight->getMonster()->name;
        QPainter painter(this);
        painter.drawText(monsterArea->pos().x()+100, monsterArea->pos().y()+50, QString::fromStdString(monsterName));
    }
}

void PlayerWindow::mousePressEvent(QMouseEvent* event)
{
//    std::cerr << event->type() << std::endl;
}

void PlayerWindow::mouseMoveEvent(QMouseEvent* event)
{

}

void PlayerWindow::playedGuiCard(Card_base* card, Card_base_gui::Target target)
{
    // Emit if there is a card
    if (card && target != Card_base_gui::Target::UNK)
    {
        Target* t = nullptr;
        Card_item* cardItem = dynamic_cast<Card_item*>(card);
        if (target == Card_base_gui::Target::SELF)
        {
            t = player;
            if (cardItem && player->cardOnTable(cardItem))
            {
                if (!cardItem->activated)
                {
                    Logger::getLogger()->log(LogType::DUMP, "Try activate " + cardItem->cardName);
                    player->tryActivate(cardItem);
                    update();
                }
                return;
            }
        }
        else if (fight && target == Card_base_gui::Target::MONSTER)
            t = fight->getMonster();
        if (cardItem && t)
            player->playCard(cardItem, t);
    }

    stateChanged();
}

void PlayerWindow::stateChanged()
{
    // Gui logic

    // HACK
    QPoint startPoint = QPoint(20, 40);
//    int offsetY = 220;
    int offsetY = ((height() - startPoint.y()) / 3);

    QPoint actCardPos = startPoint;
    const int X_DISTANCE = 20; // between cards
    for (auto& card_bunch : { {}, player->cards_table, player->cards_hand } )
    {
        actCardPos.setX(startPoint.x());
        for (auto& base_card : card_bunch)
        {
            Card_base_gui* card = exists(base_card);
            if (!card)
            {
                // Create
                Card_base_gui* cbg = new Card_base_gui(base_card, this);
                QObject::connect(cbg, &Card_base_gui::dropped, this, &PlayerWindow::playedGuiCard);
                cards.push_back(cbg);
                card = cards.back();
                Logger::getLogger()->log(LogType::DEBUG, "Card GUI " + base_card->cardName + " is created");
            }
            card->move(actCardPos);
            actCardPos.setX(actCardPos.x() + Card_base_gui::SIZE_OF_CARD.width() + X_DISTANCE);
        }
        actCardPos.setY(actCardPos.y() + offsetY);
    }

    update();
}

Card_base_gui* PlayerWindow::exists(Card_base* card) const
{
    for (auto& c : cards)
        if (c->card == card)
            return c;
    return nullptr;
}
