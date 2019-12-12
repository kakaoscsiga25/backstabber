#include "player.hpp"
#include "deck.hpp"
#include "logger.h"


Player::Player(std::string name, int level) : Target(name, level)
{
    playerClass.class_ = Class::ClassType::NONE;
}

void Player::playCard(Card_item* card, Target* target)
{
    // Remove
    bool removed = removeFromHand(card);
    if (!removed)
        removed = removeFromTable(card);
    if (removed)
        emit playCard_sign(this, card, target);
}

void Player::init(Deck* deck)
{
    // Draw new cards
//    for (int i = 0; i < 1; i++)
//    {
//        Card_base* card = deck->pullDoorCard();
//        if (card)
//            cards_hand.push_back(card);
//    }
    for (int i = 0; i < 5; i++)
    {
        Card_item* card = deck->pullTreasureCard();
        if (card)
            cards_hand.push_back(card);
    }
    dead = false;

//    Logger::getLogger()->log(LogType::DEBUG, "Player " + name + " has " + std::to_string(cards_hand.size()) + " cards in hand.");
}

void Player::levelChange(int levelChange)
{
    int initLvl = level;
    level += levelChange;

    level = std::max(level, 1); // min level is 1

    Logger::getLogger()->log(LogType::PLAY, "Player " + name + " level changed: " + std::to_string(initLvl) + "->" + std::to_string(level));
//    if (level > 10)  TODO win condition
}

bool Player::putToTable(Card_item* card)
{
//    if (!cardInHand(card)) // card is not in hand (something went wrong)
//        return false;

    // Check big size item rule
    if (card->bigSize)
        for (const auto& c : cards_table)
            if (c->bigSize)
            {
                Logger::getLogger()->log(LogType::INFO, "You can not play another \'big\' sized item!");
                return false;
            }

    // Put to table
//    if (!removeFromHand(card)) // cant remove from hand (something went wrong)
//        return false;
    cards_table.push_back(card);

    // Try to activate
    bool activated = tryActivate(card);
    Logger::getLogger()->log(LogType::DEBUG, "Card " + card->cardName + " put to table and" + ((activated)?" is":" CAN NOT") + " activated");

    return true;
}

bool Player::tryActivate(Card_item* card) const
{
    if (!cardOnTable(card))
    {
        // Card is not on the table, cant active or passive
        return false;
    }

    if (card->activated)
    {
        // Already active!
        return false;
    }

    bool canActivate = canBeActive(card);
    if (!canActivate)
        return false;

    // Hand check
    if (card->type == Card_item::ItemType::NONE)
    {
        card->activated = true;
        return true;
    }
    // else
    bool weapon = card->type & (Card_item::ItemType::ONE_HAND | Card_item::ItemType::TWO_HAND);
    int activeSameItemCounter = 0;
    for (const auto& item : cards_table)
    {
        if (!item->activated)
            continue;

        if (weapon)
        {
            if(item->type == Card_item::ItemType::ONE_HAND)
                activeSameItemCounter += 1;
            else if(item->type == Card_item::ItemType::TWO_HAND)
                activeSameItemCounter += 2;
        }
        else
            if (item->type == card->type)
                activeSameItemCounter++;
    }

    canActivate = activeSameItemCounter == 0;
    if (!canActivate && weapon)
    {
        // Two one handed?
        if (card->type == Card_item::ItemType::ONE_HAND && activeSameItemCounter < 2)
            canActivate = true;
    }

    if (canActivate)
    {
        card->activated = true;
        return true;
    }

    return false;
}

bool Player::deActivate(Card_item* card) const
{
    if (!card->activated)
        return false;
    card->activated = false;
    return true;
}

void Player::checkItems()
{
    for (auto& cardOnTable : cards_table)
        if (cardOnTable->activated)
            if (!canBeActive(cardOnTable))
            {
                cardOnTable->activated = false;
                Logger::getLogger()->log(LogType::INFO, "Card " + cardOnTable->cardName + " is inactivated!");
            }
}

bool Player::sell(Card_item* card)
{
    if (cardInHand(card) || cardOnTable(card))
    {
        int sellPrice = card->price;
        money += sellPrice;
        if (cardInHand(card))
            removeFromHand(card);
        else
            removeFromTable(card);

        Logger::getLogger()->log(LogType::INFO, "Player " + name + " sell " + card->cardName + " for " + std::to_string(sellPrice) + " gold (sum " + std::to_string(money) + ")");

        emit usedCard(card);

        const int LVL_UP_MONEY = 1000;
        int lvl = money / LVL_UP_MONEY;
        if (lvl)
        {
            levelChange(lvl);
            money -= lvl*LVL_UP_MONEY;
        }

        return true;
    }
    return false;
}

int Player::attackPower() const
{
    int powerFromItems = 0;
    for (const auto& item : cards_table)
    {
        if (item->activated)
            powerFromItems += item->bonus;
    }

    return level + powerFromItems;
}

void Player::die()
{
    for (const auto& c : cards_hand)
        emit usedCard(c);
    for (const auto& c : cards_table)
        emit usedCard(c);
    cards_hand.clear();
    cards_table.clear();
    dead = true;
    Logger::getLogger()->log(LogType::INFO, "Player " + name + " is died.");
}

void Player::changeClass(Class newClass)
{
    playerClass = newClass;
    checkItems();
}


bool Player::cardInHand(Card_item* card) const
{
    for (const auto& c : cards_hand)
        if (card == c)
            return true;
    return false;
}
bool Player::cardOnTable(Card_item* card) const
{
    for (const auto& c : cards_table)
        if (card == c)
            return true;
    return false;
}
bool Player::removeFromHand(Card_item* card)
{
    for (size_t i = 0; i < cards_hand.size(); i++)
    {
        if (card == cards_hand[i])
        {
            cards_hand.erase(cards_hand.begin()+i);
            return true;
        }
    }
    return false;
}
bool Player::removeFromTable(Card_item* card)
{
    for (size_t i = 0; i < cards_table.size(); i++)
    {
        if (card == cards_table[i])
        {
            cards_table.erase(cards_table.begin()+i);
            return true;
        }
    }
    return false;
}

bool Player::canBeActive(const Card_item* card) const
{
    bool ok = true;
    // Class check
    ok = ok && playerClass.is(card->canUsedBy);

    return ok;
}
