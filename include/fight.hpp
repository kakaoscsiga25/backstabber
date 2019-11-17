#ifndef FIGHT_HPP
#define FIGHT_HPP

#include "monster.hpp"
#include "player.hpp"
#include "logger.h"


struct Fight
{
    Fight(Monster m, Player* player, Player* helper = nullptr) : monster(m), player(player), helper(helper) {}

    bool fight() // true if the monster is defeated, false if not
    {
        int attackPlayers = player->getAttackPower();
        int healthMonster = monster.getAttackPower();

        Logger::getLogger()->log(LogType::INFO, "Fight result (player|monster): " + std::to_string(attackPlayers) + " vs. " + std::to_string(healthMonster));

        return attackPlayers > healthMonster;
    }

protected:
    Monster monster;
    Player* player;
    Player* helper;
};

#endif // FIGHT_HPP
