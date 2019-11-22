#include "gui/main_window.hpp"

#include <QPainter>


MainWindow::MainWindow()
{
//    this->setupUi(this);
    this->setFixedSize(1024,768);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter dc(this);
    QBrush pintada(Qt::green, Qt::SolidPattern);
    pintada.setColor(Qt::red);
    dc.setRenderHint(QPainter::Antialiasing,true);
    dc.setPen(QPen(Qt::black,3, Qt::DashLine, Qt::RoundCap));
    dc.setBrush(QBrush(pintada));// QBrush(Qt::green, Qt::SolidPattern)
    dc.drawEllipse(0,0,25,25);
}
