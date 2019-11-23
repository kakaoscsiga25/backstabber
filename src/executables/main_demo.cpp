#include <QApplication>
#include <QPushButton>
#include <QFrame>

#include "gui/player_window.hpp"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    PlayerWindow window;
    window.show();

    return app.exec();
}
