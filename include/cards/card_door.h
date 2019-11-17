#ifndef CARD_DOOR_H
#define CARD_DOOR_H

#include "card_base.h"
#include "player.hpp"

struct Card_door : Card_base
{
    virtual void pullEffect(Player* player) = 0;
    virtual void playEffect(Player* player, Target* toPlayer) = 0;
};

#endif // CARD_DOOR_H
