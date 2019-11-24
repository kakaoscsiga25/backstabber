#include "include/gui/player_window.hpp"
#include "ui_player_window.h"

#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <iostream>


PlayerWindow::PlayerWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);

//    QGraphicsView* gi = new QGraphicsView(this);
//    playArea = new PlayArea(this);

    card = new Card_base_gui(this);
    card->card = new Card_base("alma");

    connect(card, &Card_base_gui::clicked, this, &PlayerWindow::asd);
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}


void PlayerWindow::paintEvent(QPaintEvent* event)
{
//    QPainter painter(this);
//    QPainter painter((ui->widget));
//    painter.drawEllipse(QPointF(200,100), 10,10);

//    QImage image1;
//    image1.load("/home/gergo/dev/backstabber/data/cards/DMO_T_BG.png");
//    painter.drawImage(155, 130, image1);

//    QGraphicsPixmapItem pmi = QGraphicsPixmapItem::acceptDrops();

    card->paintEvent(event);
}

void PlayerWindow::mousePressEvent(QMouseEvent* event)
{
//    std::cerr << event->type() << std::endl;
}

void PlayerWindow::mouseMoveEvent(QMouseEvent* event)
{

}
