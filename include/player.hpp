#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "target.h"
#include "deck.hpp"
#include "cards/card_base.h"
#include "cards/card_item.h"
#include "class.h"

#include <string>
#include <vector>


struct Deck;
struct Card_base;
class Target;


class Player : public Target
{
    Q_OBJECT
public:
    Player(std::string name, int level = 100);
    virtual ~Player() = default;

    void playCard(Card_item* card, Target* target);

    void init(Deck* deck);

    void pullCard(Card_item* card) { if (card) cards_hand.push_back(card); }

    void levelChange(int levelChange);

    bool putToTable(Card_item* card);

    bool tryActivate(Card_item* card) const;
    bool deActivate(Card_item* card) const;

    void checkItems();

    bool sell(Card_item* card);

    virtual int attackPower() const;

    void die();

    bool isDead() const { return dead; }

    Class getPlayerClass() const { return playerClass; }
    void changeClass(Class newClass);


    std::vector<Card_item*> cards_hand;
    std::vector<Card_item*> cards_table;

protected:
    bool cardInHand(Card_item* card) const;
    bool cardOnTable(Card_item* card) const;
    bool removeFromHand(Card_item* card);
    bool removeFromTable(Card_item* card);

    bool canBeActive(const Card_item* card) const;

    Class playerClass;

    int money = 0;
    bool dead = false;


signals:
    void playCard_sign(Player* player, Card_item* card, Target* target);
    void usedCard(Card_item* card);
};

#endif // PLAYER_HPP
