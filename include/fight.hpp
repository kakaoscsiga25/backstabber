#ifndef FIGHT_HPP
#define FIGHT_HPP

#include <deque>

#include "monster.hpp"
#include "player.hpp"
#include "logger.h"


class Monster;
class Player;
class Deck;


class Fight : public QObject
{
    Q_OBJECT

public:
    Fight(Monster* m, Player* player, Deck* deck);
    ~Fight();

    void doFight(); // obsoleted

    void fightStatus(int& playerAttack, int& monsterAttack) const;

    void printStatus() const;

    void evaluateFight();

    Monster* getMonster() const { return monster; }

protected:
    bool tryToEscape(Player* p) const;

    Monster* monster;
    Player* player;
//    Player* helper;
    Deck* deck;

    std::deque<std::pair<Card_effect*, Target*> > playedCards;

signals:
    void discard(Card_base*);

public slots:
    void playCard(Card_effect* card, Target* target) { playedCards.push_back(std::pair<Card_effect*, Target*>(card, target)); }
};

#endif // FIGHT_HPP
