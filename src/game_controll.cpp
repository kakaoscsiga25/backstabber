#include "game_controll.hpp"
#include "turn_controll.hpp"
#include "logger.h"
#include "deck.hpp"

#include <assert.h>


GameControll::GameControll(int numberOfPlayers)
{
    for (int i = 0; i < numberOfPlayers; i++)
        players.push_back(Player(std::to_string(i+1))); // init players
    Logger::getLogger()->log(LogType::INFO, std::to_string(players.size()) + " player are initialized");
}

void GameControll::start()
{
    Logger::getLogger()->log(LogType::PLAY, "Game is started with " + std::to_string(players.size()) + " player.");

    // Init players
    for (auto& player : players)
    {
        Logger::getLogger()->log(LogType::DEBUG, "Player " + player.getName() + " initializing...");
        player.init();
        Logger::getLogger()->log(LogType::DEBUG, "Player " + player.getName() + " is initialized.");
    }

    // Select first player
    assert(!players.empty());
    int pidx = 0;
    bool finished = false;
    while (!finished)
    {
        Player* activePlayer = &(players.at(pidx));
        pidx = (pidx+1)%players.size(); // move to next

        TurnControll turnControll(activePlayer, &players);
        turnControll.turn();

        break; // hack
    }

}
