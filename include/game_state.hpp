#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "player.hpp"
#include "deck.hpp"
#include "fight.hpp"


struct Card_base;
struct Deck;


class GameState : public QObject
{
    Q_OBJECT
public:
    virtual ~GameState();

    std::vector<Player*> players;
    Deck* deck = nullptr;
    Fight* fight = nullptr;
};


#endif // GAME_STATE_HPP
