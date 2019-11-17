#ifndef CARD_MONSTER_H
#define CARD_MONSTER_H

#include "card_door.h"
#include "fight.hpp"
#include "logger.h"

class CardMonster : public Card_door
{
public:
    CardMonster(Monster m) : Card_door(m.getName()), monster(m) {}

    virtual void pullEffect(Player* player)
    {
        Fight f(monster, player);
        if (f.fight()) // defeated
        {
            Logger::getLogger()->log(LogType::PLAY, "Monster " + monster.getName() + " is defeated.");
            monster.reward(player);
        }
        else
        {
            Logger::getLogger()->log(LogType::PLAY, "Player is defeated by " + monster.getName());
            monster.sucks(player);
        }
    }
    virtual void playEffect(Player* player, Target* toPlayer)
    {

    }

protected:
    Monster monster;
};


#endif // CARD_MONSTER_H
