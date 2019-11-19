#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "target.h"
#include "deck.hpp"
#include "cards/card_base.h"

#include <string>
#include <vector>


struct Deck;
struct Card_base;


class Player : public Target
{
    Q_OBJECT
public:
    Player(std::string name, int level = 100) : Target("'"+name+"'", level) {}
    virtual ~Player() = default;

    void init(Deck* deck);

    void addCard(Card_base* card) { if (card) cards_hand.push_back(card); }

    void levelUp(int levelUp);


    std::vector<Card_base*> cards_hand;
    std::vector<Card_base*> cards_table;


signals:
    void playCard(Card_base*, Target*);
};

#endif // PLAYER_HPP
