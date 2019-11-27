#define protected public
#define private public

#include <iostream>
#include <unistd.h>
#include <thread>

#include "target.h"
#include "player.hpp"
#include "deck.hpp"
#include "game_controll.hpp"
#include "cards/card_monster.h"

using namespace std;


int main()
{
    GameControll gc;

    Player* p = gc.state.player;
//    std::cerr << std::this_thread::get_id() << std::endl;

    // Do some player action
    sleep(1);
    gc.playCardRequest(p->cards_hand.front(), p); // try to play first card (put  to table)
    sleep(1);
    gc.playCardRequest(p->cards_hand.front(), p); // try to play first card (put  to table)

    while(!gc.state.fight)
    {
        sleep(1);
    }
    gc.playCardRequest(p->cards_hand.front(), gc.state.fight->monster); // play first hand card to monster
    sleep(1);
    gc.playCardRequest(p->cards_table.front(), gc.state.fight->monster); // play first table card to monster

    sleep(5);




//    Player p("En", 1);
//    Deck deck;
//    QObject::connect(&p, &Player::usedCard, &deck, &Deck::discard);

//    p.init(&deck);


//    for (int i=0;i<5;i++)
//    {
//        if (p.dead)
//            p.init(&deck);

//        // Try put to table all card
//        for (size_t i = 0; i < p.cards_hand.size();)
//            if (!p.putToTable(p.cards_hand.at(i)))
//                i++;

//        Card_monster* monsterCard = deck.pullDoorCard();
//        monsterCard->fightWithMonster(&p, &deck);
//    }


    return 0;
}
