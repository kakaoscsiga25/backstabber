#define protected public
#define private public

#include <iostream>

#include "target.h"
#include "player.hpp"
#include "deck.hpp"
#include "game_controll.hpp"
#include "cards/card_monster.h"

using namespace std;


int main()
{
    Player p("En", 1);
    Deck deck;
    QObject::connect(&p, &Player::usedCard, &deck, &Deck::discard);

    p.init(&deck);


    for (int i=0;i<5;i++)
    {
        if (p.dead)
            p.init(&deck);

        // Try put to table all card
        for (size_t i = 0; i < p.cards_hand.size();)
            if (!p.putToTable(p.cards_hand.at(i)))
                i++;

        Card_monster* monsterCard = deck.pullDoorCard();
        monsterCard->fightWithMonster(&p, &deck);
    }


    return 0;
}
