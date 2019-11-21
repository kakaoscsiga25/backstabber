#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "player.hpp"
#include "deck.hpp"
#include "fight.hpp"


class Card_base;
class Deck;
class Player;


class GameState : public QObject
{
    Q_OBJECT
public:
    virtual ~GameState();

//    std::vector<Player*> players;
    Player* player;
    Deck* deck = nullptr;
//    Fight* fight = nullptr;
};


#endif // GAME_STATE_HPP
