#include "include/gui/player_window.hpp"
#include "ui_player_window.h"

#include <QPainter>


PlayerWindow::PlayerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}


void PlayerWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawEllipse(QPointF(100,100), 10,10);
}

void PlayerWindow::mousePressEvent(QMouseEvent* event)
{
//    std::cerr <<
}

void PlayerWindow::mouseMoveEvent(QMouseEvent* event)
{

}
