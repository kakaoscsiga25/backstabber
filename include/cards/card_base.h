#ifndef CARDS_BASE_H
#define CARDS_BASE_H

#include <string>
#include "game_state.hpp"


class GameState;


struct Card_base
{
    Card_base(std::string name) : cardName(name) {}
    virtual ~Card_base() = default;

    virtual bool playCard(GameState* state) { return false; }

    std::string cardName;
};

#endif // CARDS_BASE_H
