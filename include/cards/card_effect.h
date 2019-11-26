#ifndef CARD_EFFECT_H
#define CARD_EFFECT_H

#include "card_item.h"


class Card_effect : public Card_item
{
public:
    Card_effect(std::string ID, std::string name, int changeValue, int bonus = 0, int price = 0, ItemType type = ItemType::NONE, bool big = false)
        : Card_item(ID, name, bonus, price, type, big), changeValue(changeValue) {}

    int changeValue;
};


#endif // CARD_EFFECT_H
