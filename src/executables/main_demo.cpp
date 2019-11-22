#include <QApplication>

#include "gui/main_window.hpp"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow window;
//    window.ex

    return app.exec();
}
