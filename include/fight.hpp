#ifndef FIGHT_HPP
#define FIGHT_HPP

#include <deque>

#include "monster.hpp"
#include "player.hpp"
#include "logger.h"


class Monster;
class Player;
class Deck;


struct Fight
{
    Fight(Monster* m, Player* player, Deck* deck);

    void doFight();

protected:
    bool tryToEscape(Player* p) const;

    Monster* monster;
    Player* player;
//    Player* helper;
    Deck* deck;

    std::deque<std::pair<Card_effect*, Target*> > playedCards;

public slots:
    void playCard(Card_effect* card, Target* target) { playedCards.push_back(std::pair<Card_effect*, Target*>(card, target)); }
};

#endif // FIGHT_HPP
