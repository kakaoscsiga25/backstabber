#include "player.hpp"
#include "deck.hpp"
#include "logger.h"


void Player::init()
{
    Logger::getLogger()->log(LogType::DEBUG, "Player " + name + " discard " + std::to_string(cards_hand.size()) + " card from the hand");
    Logger::getLogger()->log(LogType::DEBUG, "Player " + name + " discard " + std::to_string(cards_table.size()) + " card from the table");

    for(auto& card : cards_hand)
        Deck::getDeck()->discard(card);
    cards_hand.clear();
    for(auto& card : cards_table)
        Deck::getDeck()->discard(card);
    cards_table.clear();

    // Draw new cards
    for (int i = 0; i < 1; i++)
    {
        Card_base* card = Deck::getDeck()->pullDoorCard();
        if (card)
            cards_hand.push_back(card);
    }
    for (int i = 0; i < 3; i++)
    {
        Card_base* card = Deck::getDeck()->pullTreasureCard();
        if (card)
            cards_hand.push_back(card);
    }

    Logger::getLogger()->log(LogType::DEBUG, "Player " + name + " has " + std::to_string(cards_hand.size()) + " cards in hand.");
}

void Player::levelUp(int levelUp)
{
    int initLvl = level;
    level += levelUp;
    Logger::getLogger()->log(LogType::PLAY, "Player " + name + " level up: " + std::to_string(initLvl) + "->" + std::to_string(level));
//    if (level > 10)  TODO win condition
}
