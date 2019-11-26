#ifndef CARD_ITEM_H
#define CARD_ITEM_H

#include <string>

#include "card_base.h"


class Card_item : public Card_base
{
public:
    enum ItemType {
        NONE        = 0,
        ONE_HAND    = 1,
        TWO_HAND    = 2,
        HEAD        = 4,
        FOOT        = 8,
        ARMOR       = 16,

        WEAPON      = ONE_HAND | TWO_HAND,
    };

    Card_item(std::string ID, std::string name, int bonus = 0, int price = 0, ItemType type = NONE, bool bigSize = false) :
        Card_base(ID, name), bonus(bonus), price(price), type(type), bigSize(bigSize) {}
    virtual ~Card_item() = default;


    int bonus;
    int price;
    ItemType type;
    bool activated = false; // on the table
    bool bigSize;
};


#endif // CARD_ITEM_H
