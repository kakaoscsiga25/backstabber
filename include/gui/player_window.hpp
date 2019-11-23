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

private:
    Ui::PlayerWindow *ui;
};

#endif // PLAYER_WINDOW_HPP
