#include "fight.hpp"
#include <unistd.h>


Fight::Fight(Monster* m, Player* player, Deck* deck) : monster(m), player(player), deck(deck)
{
    Logger::getLogger()->log(LogType::DEBUG, "Fight initialized between " + player->name + " (player) and " + m->name + " (monster).");

    connect(this, &Fight::discard, deck, &Deck::discard);
    printStatus();
}
Fight::~Fight()
{
    for (auto& c : playedCards)
        emit discard(c.first);
    playedCards.clear();
    Logger::getLogger()->log(LogType::DEBUG, "Fight ended, card discarded");
}

void Fight::doFight()
{
    int playerAttack = player->attackPower();
    int monsterAttack = monster->attackPower();

    // Wait for interactions
    int waitTime = 5;
    int waited = 0;
    while(waitTime > waited)
    {
        if (!playedCards.empty())
        {
            for (size_t i = 0; i < playedCards.size(); i++)
            {
                // Apply the card effects
                Card_effect* card = playedCards[i].first;
                Target* target = playedCards[i].second;
                target->addNewEffectCard(card);
            }
            playedCards.clear();

            playerAttack = player->attackPower() + player->evaluateCardEffects();
            monsterAttack = monster->attackPower() + monster->evaluateCardEffects();

            Logger::getLogger()->log(LogType::INFO, "CHANGED STATS: Player vs. Monster: " + std::to_string(playerAttack) + ":" + std::to_string(monsterAttack));
        }

        Logger::getLogger()->log(LogType::DEBUG, "Wait for action... " + std::to_string(waitTime - waited));
        sleep(1);
        waited += 1;
    }

    Logger::getLogger()->log(LogType::INFO, "Player vs. Monster: " + std::to_string(playerAttack) + ":" + std::to_string(monsterAttack));

    // Final evaluation
    bool defeat = playerAttack > monsterAttack;
    if (!defeat && player->getPlayerClass().is(Class::ClassType::WARRIOR) && playerAttack == monsterAttack) // warrior can beat the monster with equal strength
        defeat = true;

    if (defeat)
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

void Fight::fightStatus(int& playerAttack, int& monsterAttack) const
{
    playerAttack = player->attackPower() + player->evaluateCardEffects();
    monsterAttack = monster->attackPower() + monster->evaluateCardEffects();
}

void Fight::printStatus() const
{
    int playerAttack, monsterAttack;
    fightStatus(playerAttack, monsterAttack);
    Logger::getLogger()->log(LogType::INFO, "Player vs. Monster: " + std::to_string(playerAttack) + ":" + std::to_string(monsterAttack));
}

void Fight::evaluateFight()
{
    // Final evaluation
    int playerAttack, monsterAttack;
    fightStatus(playerAttack, monsterAttack);
    bool defeat = playerAttack > monsterAttack;
    if (!defeat && player->getPlayerClass().is(Class::ClassType::WARRIOR) && playerAttack == monsterAttack) // warrior can beat the monster with equal strength
        defeat = true;

    if (defeat)
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
