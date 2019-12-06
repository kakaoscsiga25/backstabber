#ifndef CARD_MONSTER_H
#define CARD_MONSTER_H

#include "monster.hpp"
#include "fight.hpp"


class Card_monster : public Card_base
{
public:
    Card_monster(std::string ID, std::string name, int level, int treasures, int levelReward, Monster::BadStuffs badThing) :
        Card_base(ID, name), monster(name, level, treasures, levelReward, badThing) {}

//    void fightWithMonster(Player* player, Deck* deck)
//    {
//        Fight f(&monster, player, deck);
//        f.doFight();
//        deck->discard(this);
//    }


//protected:
    Monster monster;
};


#endif // CARD_MONSTER_H
