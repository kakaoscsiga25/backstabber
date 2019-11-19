#ifndef CARD_TREASURE_H
#define CARD_TREASURE_H

#include "card_base.h"

struct Card_treasure : public Card_base
{
    Card_treasure(std::string name) : Card_base(name) {}
};

#endif // CARD_TREASURE_H
