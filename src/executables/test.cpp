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

    p.deActivate(p.cards_table.at(1));
    p.deActivate(p.cards_table.at(7));

    p.tryActivate(p.cards_table.at(8));

    return 0;
}
