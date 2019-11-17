#ifndef DECK_HPP
#define DECK_HPP

#include "cards/card_door.h"
#include "cards/card_treasure.h"
#include <vector>
#include <algorithm>


class Deck
{
public:
    static Deck* getDeck()
    {
        static Deck deck;
        return &deck;
    }

    Card_door* pullDoorCard()
    {
        if (door_deck.empty())
        {
            reshuffleDoorCards(); // try reshuffle
            if (door_deck.empty())
                return nullptr;
        }
        Card_door* card = door_deck.back();
        door_deck.pop_back();
        return card;
    }

    Card_treasure* pullTreasureCard();

protected:
    void reshuffleDoorCards()
    {
        door_deck.insert(door_deck.end(), door_deck_used.begin(), door_deck_used.end());
        door_deck_used.clear();
        std::random_shuffle(door_deck.begin(), door_deck.end());
    }
    void reshuffleTreasureCards()
    {
        treasure_deck.insert(treasure_deck.end(), treasure_deck_used.begin(), treasure_deck_used.end());
        treasure_deck_used.clear();
        std::random_shuffle(treasure_deck.begin(), treasure_deck.end());
    }

    std::vector<Card_door*> door_deck;
    std::vector<Card_door*> door_deck_used;
    std::vector<Card_treasure*> treasure_deck;
    std::vector<Card_treasure*> treasure_deck_used;
};


#endif // DECK_HPP
