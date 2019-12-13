#include <QApplication>
#include <QPushButton>
#include <QFrame>
#include <unistd.h>

#include "game_controll.hpp"
#include "gui/player_window.hpp"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    GameControll gc;

    Player* p = gc.getState()->player;

    PlayerWindow window(&gc);

    QObject::connect(&gc, &GameControll::somethingChanged, &window, &PlayerWindow::stateChanged);

    window.stateChanged(); // init
    window.show();


    return app.exec();
}
