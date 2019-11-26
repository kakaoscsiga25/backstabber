#ifndef PLAYER_WINDOW_HPP
#define PLAYER_WINDOW_HPP

#include <QMainWindow>

#include "gui/card_base_gui.hpp"
#include "gui/hand_area.hpp"
#include <iostream>


namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = 0);
    ~PlayerWindow();

    void paintEvent(QPaintEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
//    void mouseReleaseEvent(QMouseEvent* event)
//    {
//        Card_base_gui *child = dynamic_cast<Card_base_gui*>(childAt(event->pos()));
//        if (child)
//            std::cerr << "REL on " << child << "\n";
//        else
//            std::cerr << "no \n";
//    }
    void asdasd()
    {
        std::cerr << "parent call \n";
    }

private:
    Ui::PlayerWindow *ui;

//    PlayArea* playArea;
    Card_base_gui* card;
    Card_base_gui* card2;

public slots:
    void asd(QPoint pos) {
        std::cerr << pos.x() << " " << pos.y() << "\n";
//        card->is
    }
};

#endif // PLAYER_WINDOW_HPP
