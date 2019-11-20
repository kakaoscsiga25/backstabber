#include "game_state.hpp"

GameState::~GameState()
{
//    for (auto& player : players)
    {
//        player->disconnect();
//        delete player;
    }
//    players.clear();
    delete deck;
//    delete fight;
}
