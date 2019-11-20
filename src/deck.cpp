#include "deck.hpp"
#include "cards/card_monster.h"
#include "logger.h"

Deck::Deck()
{
    // Initialize doors deck
//    door_deck.push_back(new CardMonster(new Monster("1lvl monster", 1, 1)));
//    door_deck.push_back(new CardMonster(new Monster("5lvl monster", 5, 1)));
//    door_deck.push_back(new CardMonster(new Monster("10lvl monster", 10, 2)));
//    door_deck.push_back(new CardMonster(new Monster("20lvl monster", 20, 4)));


//    treasure_deck.push_back(new Card_treasure("K1"));
//    treasure_deck.push_back(new Card_treasure("K2"));

//    treasure_deck.push_back();


    std::random_shuffle(door_deck.begin(), door_deck.end());
}
Deck::~Deck()
{
    std::vector<std::vector<Card_base*> > decks(4);// = { door_deck, door_deck_used, treasure_deck, treasure_deck_used };
    for (auto& a : door_deck)
        decks.at(0).push_back(a);
    for (auto& a : door_deck_used)
        decks.at(1).push_back(a);
    for (auto& a : treasure_deck)
        decks.at(2).push_back(a);
    for (auto& a : treasure_deck_used)
        decks.at(3).push_back(a);
    for (auto& deck : decks)
    {
        for (auto& card : deck)
            delete card;
        deck.clear();
    }
}

Card_door* Deck::pullDoorCard()
{
    if (door_deck.empty())
    {
        reshuffleDoorCards(); // try reshuffle
        if (door_deck.empty())
            return nullptr;
    }
    Card_door* card = door_deck.back();
    door_deck.pop_back();

    Logger::getLogger()->log(LogType::INFO, "Drawed door card name: " + card->cardName);

    return card;
}
Card_treasure* Deck::pullTreasureCard()
{
    if (treasure_deck.empty())
    {
        reshuffleTreasureCards(); // try reshuffle
        if (treasure_deck.empty())
            return nullptr;
    }
    Card_treasure* card = treasure_deck.back();
    treasure_deck.pop_back();

    Logger::getLogger()->log(LogType::INFO, "Drawed treasure card name: " + card->cardName);

    return card;
}

void Deck::discard(Card_base* _card)
{
    if (Card_door* card = dynamic_cast<Card_door*>(_card))
    {
        Logger::getLogger()->log(LogType::DUMP, "Discarded door card: " + card->cardName);
        door_deck_used.push_back(card);
    }
    else if (Card_treasure* card = dynamic_cast<Card_treasure*>(_card))
    {
        Logger::getLogger()->log(LogType::DUMP, "Discarded treasure card: " + card->cardName);
        treasure_deck_used.push_back(card);
    }
    else
        Logger::getLogger()->log(LogType::FATAL, "Unknown discarded card type.");
}

void Deck::reshuffleDoorCards()
{
    door_deck.insert(door_deck.end(), door_deck_used.begin(), door_deck_used.end());
    door_deck_used.clear();
    std::random_shuffle(door_deck.begin(), door_deck.end());
}
void Deck::reshuffleTreasureCards()
{
    treasure_deck.insert(treasure_deck.end(), treasure_deck_used.begin(), treasure_deck_used.end());
    treasure_deck_used.clear();
    std::random_shuffle(treasure_deck.begin(), treasure_deck.end());
}
