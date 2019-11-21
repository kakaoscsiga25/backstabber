#include "fight.hpp"


void Fight::doFight()
{
    int playerAttack = player->attackPower();
    int monsterAttack = monster->attackPower();

    Logger::getLogger()->log(LogType::INFO, "Player vs. Monster: " + std::to_string(playerAttack) + ":" + std::to_string(monsterAttack));

    if (playerAttack > monsterAttack)
    {
        Logger::getLogger()->log(LogType::INFO, "Monster " + monster->name + " is defeated by " + player->name);
        monster->reward(player, deck);
    }
    else
    {
        bool escaped = tryToEscape(player);

        if (!escaped)
        {
            Logger::getLogger()->log(LogType::INFO, "Player " + player->name + " is defeated and can\'t escape. Bad thing comes...");
            monster->badStuff(player);
        }
    }
}

bool Fight::tryToEscape(Player* p) const
{
    int dice = rand()%6;
    int MINIMUM_ESCAPE_SCORE = 5;
    Logger::getLogger()->log(LogType::DEBUG, "Escape dice: " + std::to_string(dice) + " (min:" + std::to_string(MINIMUM_ESCAPE_SCORE) + ")");
    return dice >= MINIMUM_ESCAPE_SCORE;
}
