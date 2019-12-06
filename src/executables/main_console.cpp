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
    Logger::getLogger()->log(LogType::DEBUG, "MAIN: Try play: " + p->cards_hand.front()->cardName);
    p->playCard(p->cards_hand.front(), p); // try to play first card (put  to table)
    sleep(1);
    Logger::getLogger()->log(LogType::DEBUG, "MAIN: Try play: " + p->cards_hand.front()->cardName);
    p->playCard(p->cards_hand.front(), p); // try to play first card (put  to table)

    while(!gc.state.fight)
    {
        sleep(1);
    }
    Logger::getLogger()->log(LogType::DEBUG, "MAIN: Try play: " + p->cards_hand.front()->cardName);
    p->playCard(p->cards_hand.front(), p); // try to play first card (put  to table)
    sleep(1);
    Logger::getLogger()->log(LogType::DEBUG, "MAIN: Try play: " + p->cards_hand.front()->cardName);
    p->playCard(p->cards_hand.front(), p); // try to play first card (put  to table)

    Logger::getLogger()->log(LogType::DEBUG, "MAIN: Wait to game controll thread...");
    gc.wait();

    Logger::getLogger()->log(LogType::DEBUG, "MAIN: Finished");
    return 0;
}
