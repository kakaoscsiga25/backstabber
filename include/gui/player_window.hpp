#ifndef PLAYER_WINDOW_HPP
#define PLAYER_WINDOW_HPP

#include <QMainWindow>

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
};

#endif // PLAYER_WINDOW_HPP
