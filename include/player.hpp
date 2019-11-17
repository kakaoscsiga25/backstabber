#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "target.h"
#include "cards/card_base.h"

#include <string>
#include <vector>


class Player : public Target
{
public:
    Player(std::string name, int level = 100) : Target("'"+name+"'", level) {}

    void init();

    void addCard(Card_base* card) { if (card) cards_hand.push_back(card); }

    void levelUp(int levelUp);

protected:
    std::vector<Card_base*> cards_hand;
    std::vector<Card_base*> cards_table;
};

#endif // PLAYER_HPP
