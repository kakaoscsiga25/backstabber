#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "target.h"

#include <string>


class Player : Target
{
public:
    Player()
    {
        // Init name
        static int playerNum = 0;
        name = std::to_string(++playerNum); // HACKY
    }

    void init() {} // TODO

    std::string getName() const { return name; }


protected:
};

#endif // PLAYER_HPP
