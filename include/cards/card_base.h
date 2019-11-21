#ifndef CARDS_BASE_H
#define CARDS_BASE_H

#include <string>


class Card_base
{
public:
    Card_base(std::string name) : cardName(name) {}
    virtual ~Card_base() = default;

//    virtual bool playCard(Target* target, GameState* state) { return false; }

    std::string cardName;
};

#endif // CARDS_BASE_H
