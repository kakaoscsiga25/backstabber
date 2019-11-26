#ifndef CARD_DOOR_H
#define CARD_DOOR_H

#include "card_base.h"
#include "player.hpp"


class Player;


struct Card_door : public Card_base
{
    Card_door(std::string ID, std::string cardName) : Card_base(ID, cardName) {}
    virtual ~Card_door() {}

    virtual void pullEffect(Player* player) = 0;
};

#endif // CARD_DOOR_H
