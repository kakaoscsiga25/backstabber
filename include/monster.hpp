#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "target.h"
#include "player.hpp"
#include "deck.hpp"
#include "logger.h"


class Player;
class Deck;


class Monster : public Target
{
    Q_OBJECT
public:
    enum BadStuffs
    {
        NOTHING     =   0,
        DIE         =   1,
        LOSE_LVL    =   2,
    };

    Monster(std::string name, int level, int treasures, int levelReward, BadStuffs badThing) :
        Target(name, level), rewardTreasure(treasures), levelReward(levelReward), suck(badThing) {}

    void reward(Player* player, Deck* deck) const;

    void badStuff(Player* player) const;

protected:
    int rewardTreasure;
    int levelReward; // if the monster is defeated
    BadStuffs suck;
};

#endif // MONSTER_HPP
