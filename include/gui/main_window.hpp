#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    void paintEvent(QPaintEvent *e);

};

#endif // WINDOW_HPP
