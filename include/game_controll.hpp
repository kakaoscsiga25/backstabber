#ifndef GAME_CONTROLL_HPP
#define GAME_CONTROLL_HPP

#include "player.hpp"

#include <vector>


class GameControll
{
public:
    GameControll(int numberOfPlayers = 2);


    void start();

protected:
    std::vector<Player> players;
};


#endif // GAME_CONTROLL_HPP
