#ifndef GAME_CONTROLL_HPP
#define GAME_CONTROLL_HPP

#include "player.hpp"
#include "game_state.hpp"

#include <vector>
#include <QObject>


class GameControll : public QObject
{
    Q_OBJECT
public:
    GameControll(int numberOfPlayers = 2);
    virtual ~GameControll() = default;

    void start();

    void turn(Player* activePlayer);

protected:
    GameState state;


public slots:
    void playCardRequest(Card_base* card, Target* target);
};


#endif // GAME_CONTROLL_HPP
