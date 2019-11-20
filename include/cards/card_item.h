#ifndef CARD_ITEM_H
#define CARD_ITEM_H

#include <string>




class Card_item
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

    Card_item(std::string name, int bonus = 0, int price = 0, ItemType type = NONE) : name(name), bonus(bonus), price(price), type(type) {}
    virtual ~Card_item() = default;


    std::string name;

    int bonus;
    int price;
    ItemType type;
    bool activated = false; // on the table
};


#endif // CARD_ITEM_H
