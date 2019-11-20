#include "game_controll.hpp"
#include "logger.h"
#include "deck.hpp"

#include <assert.h>


GameControll::GameControll(int numberOfPlayers)
{
//    for (int i = 0; i < numberOfPlayers; i++)
//    {
//        state.players.push_back(new Player(std::to_string(i+1))); // init players
//        QObject::connect(state.players.back(), &Player::playCard, this, &GameControll::playCardRequest, Qt::DirectConnection);
//    }
//    Logger::getLogger()->log(LogType::INFO, std::to_string(state.players.size()) + " player are initialized");

//    state.deck = new Deck();
}

void GameControll::start()
{
//    Logger::getLogger()->log(LogType::PLAY, "Game is started with " + std::to_string(state.players.size()) + " player.");

//    // Init players
//    for (auto& player : state.players)
//    {
//        player->init(state.deck);
//    }

//    // Select first player
//    assert(!state.players.empty());
//    int pidx = 0;
//    bool finished = false;
//    while (!finished)
//    {
//        Player* activePlayer = (state.players.at(pidx));
//        pidx = (pidx+1)%state.players.size(); // move to next

//        turn(activePlayer);

//        break; // hack
//    }

}

void GameControll::turn(Player* activePlayer)
{

}

void GameControll::playCardRequest(Card_base* card, Target* target)
{
    std::cerr << QObject::sender() << " request " << target << "\n";
}
