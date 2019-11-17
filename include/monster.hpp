#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "target.h"
#include "player.hpp"
#include "deck.hpp"
#include "logger.h"


class Monster : public Target
{
public:
    Monster(std::string name, int level, int treasures, int levelUp = 1) : Target(name, level), rewardTreasure(treasures), levelUp(levelUp) {}

    void reward(Player* player)
    {
        player->levelUp(levelUp);
        for (int i = 0; i < rewardTreasure; i++)
            player->addCard(Deck::getDeck()->pullTreasureCard());
    }

    void sucks(Player* player)
    {
        Logger::getLogger()->log(LogType::DEBUG, "Monster suck is now kill.");
        player->init();
    }

protected:
    int rewardTreasure;
    int levelUp;
};

#endif // MONSTER_HPP
