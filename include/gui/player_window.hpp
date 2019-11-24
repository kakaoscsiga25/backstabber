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

private:
    Ui::PlayerWindow *ui;

//    PlayArea* playArea;
    Card_base_gui* card;

public slots:
    void asd() { std::cerr << "clicked\n"; }
};

#endif // PLAYER_WINDOW_HPP
