#ifndef DECK_HPP
#define DECK_HPP

#include "cards/card_door.h"
#include "cards/card_treasure.h"
#include "cards/card_item.h"
#include <vector>
#include <algorithm>


class Deck
{
protected:

public:
    Deck(); // init
    ~Deck();

//    Card_door pullDoorCard();
    Card_item* pullTreasureCard();

    void discard(Card_base* card);

protected:
    void reshuffleDoorCards();
    void reshuffleTreasureCards();

    std::vector<Card_door*> door_deck;
    std::vector<Card_door*> door_deck_used;
    std::vector<Card_item*> treasure_deck;
    std::vector<Card_item*> treasure_deck_used;
};


#endif // DECK_HPP
