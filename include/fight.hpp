#ifndef FIGHT_HPP
#define FIGHT_HPP

#include "monster.hpp"
#include "player.hpp"
#include "logger.h"


class Monster;
class Player;
class Deck;


struct Fight
{
    Fight(Monster* m, Player* player, Deck* deck) : monster(m), player(player), deck(deck) {}

    void doFight();

protected:
    bool tryToEscape(Player* p) const;

    Monster* monster;
    Player* player;
//    Player* helper;
    Deck* deck;
};

#endif // FIGHT_HPP
