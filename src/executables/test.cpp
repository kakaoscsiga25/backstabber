#define protected public
#define private public

#include <iostream>

#include "target.h"
#include "player.hpp"
#include "deck.hpp"
#include "game_controll.hpp"

using namespace std;

int main()
{
    Player p("En", 1);
    Deck deck;

    QObject::connect(&p, &Player::usedCard, &deck, &Deck::discard);


    while (auto card = deck.pullTreasureCard())
    {
        p.pullCard(card);
        p.putToTable(p.cards_hand.front());
    }

    cerr << p.attackPower() << "\n";

    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));
    p.sell(p.cards_table.at(3));

    cerr << p.attackPower() << "\n";

    return 0;
}
