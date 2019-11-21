#define protected public
#define private public

#include <iostream>

#include "target.h"
#include "player.hpp"
#include "deck.hpp"
#include "game_controll.hpp"


int main()
{
    Player p("En", 1);
    Deck deck;


    while (auto card = deck.pullTreasureCard())
    {
        p.addCard(card);
        p.putToTable(p.cards_hand.front());
    }

    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));

    return 0;
}
