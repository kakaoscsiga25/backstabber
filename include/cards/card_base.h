#ifndef CARDS_BASE_H
#define CARDS_BASE_H

#include <string>

struct Card_base
{
    Card_base(std::string name) : cardName(name) {}
    virtual ~Card_base() {}

    std::string cardName;
};

#endif // CARDS_BASE_H
