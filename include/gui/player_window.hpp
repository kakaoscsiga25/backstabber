#ifndef PLAYER_WINDOW_HPP
#define PLAYER_WINDOW_HPP

#include <QMainWindow>
#include <memory>

#include "gui/card_base_gui.hpp"
#include "game_controll.hpp"



namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QMainWindow
{
    Q_OBJECT

public:
    PlayerWindow(GameControll* gc, QWidget *parent = nullptr);
    ~PlayerWindow();

    void paintEvent(QPaintEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    void resizeEvent(QResizeEvent* event)
    {
       QMainWindow::resizeEvent(event);
       stateChanged();
    }

private:
    Card_base_gui* exists(Card_base* card) const;

    Player* player;
    Fight* fight = nullptr;
    std::vector<Card_base_gui*> cards;

    Ui::PlayerWindow *ui;
    QFrame* handArea = nullptr;
    QFrame* itemsArea = nullptr;
    QFrame* monsterArea = nullptr;

signals:
//    void refresh();

public slots:
    void playedGuiCard(Card_base* card, Card_base_gui::Target target);
    void stateChanged();

    void fightStarted(Fight* f) { fight = f; }
    void fightEnded() { fight = nullptr; }
};

#endif // PLAYER_WINDOW_HPP
