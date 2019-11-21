#include "monster.hpp"


void Monster::reward(Player* player, Deck* deck) const
{
    player->levelChange(levelReward);
    for (int i = 0; i < rewardTreasure; i++)
        player->pullCard(deck->pullTreasureCard());
}

void Monster::badStuff(Player* player) const
{
    if (suck & BadStuffs::DIE)
    {
        player->die();
    }
    if (suck & BadStuffs::LOSE_LVL)
    {
        player->levelChange(-1);
    }

}
