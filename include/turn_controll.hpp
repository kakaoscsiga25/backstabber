#ifndef TURN_CONTROLL_HPP
#define TURN_CONTROLL_HPP

#include "player.hpp"
#include "logger.h"

#include <vector>


class TurnControll
{
public:
    TurnControll(Player* activePlayer, std::vector<Player>* allPlayer);

    void turn();


protected:
    void phase_1();
    void phase_2();
    void phase_3();

    Player* activePlayer;
    std::vector<Player>* allPlayer;
};


#endif // TURN_CONTROLL_HPP
