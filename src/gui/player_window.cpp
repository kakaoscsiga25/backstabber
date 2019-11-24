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
    card->move(100,100);

    card2 = new Card_base_gui(this);
    card2->card = new Card_base("asd");
    card2->move(300,100);


    connect(card, &Card_base_gui::clicked, this, &PlayerWindow::asd);
    connect(card2, &Card_base_gui::clicked, this, &PlayerWindow::asd);
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}


void PlayerWindow::paintEvent(QPaintEvent* event)
{

}

void PlayerWindow::mousePressEvent(QMouseEvent* event)
{
//    std::cerr << event->type() << std::endl;
}

void PlayerWindow::mouseMoveEvent(QMouseEvent* event)
{

}
