#define protected public
#define private public

#include <iostream>

#include "target.h"
#include "player.hpp"
#include "deck.hpp"
#include "game_controll.hpp"


int main()
{

    GameControll gc;

    GameState* state = &gc.state;

    for (auto& player : state->players)
        player->init(state->deck);

    Player* p = state->players.front();

    std::cerr << "Player ptr " << p << "\n";

    emit p->playCard(p->cards_hand.front(), p);


    return 0;
}
