#include "deck.hpp"
#include "cards/card_monster.h"
#include "cards/card_item.h"
#include "logger.h"

Deck::Deck()
{
    // Initialize doors deck
    door_deck.push_back(new Card_monster("Squidzilla", 18, 4, 2, Monster::BadStuffs::DIE));
    door_deck.push_back(new Card_monster("Plutonium dragon", 20, 5, 2, Monster::BadStuffs::DIE));
    door_deck.push_back(new Card_monster("Large angry chicken", 2, 1, 1, Monster::BadStuffs::LOSE_LVL));
    std::random_shuffle(door_deck.begin(), door_deck.end());

    treasure_deck.push_back(new Card_item("Spiky knee\'s",      1,  200,    Card_item::ItemType::NONE       ));
    treasure_deck.push_back(new Card_item("Eleven-foot pole",   1,  200,    Card_item::ItemType::TWO_HAND   ));
    treasure_deck.push_back(new Card_item("Rat on a stick",     1,  0,      Card_item::ItemType::ONE_HAND   ));
    treasure_deck.push_back(new Card_item("Helm of courage",    1,  200,    Card_item::ItemType::HEAD       ));
    treasure_deck.push_back(new Card_item("Hireling",           1,  0,      Card_item::ItemType::NONE       ));
    treasure_deck.push_back(new Card_item("Horny helmet",       1,  600,    Card_item::ItemType::HEAD       )); // TODO: +3 if elf
    treasure_deck.push_back(new Card_item("Slimy armor",        1,  200,    Card_item::ItemType::ARMOR      ));
    treasure_deck.push_back(new Card_item("Leather armor",      1,  300,    Card_item::ItemType::ARMOR      ));
    treasure_deck.push_back(new Card_item("Buckler of swashing",2,  400,    Card_item::ItemType::ONE_HAND   ));
    treasure_deck.push_back(new Card_item("Dancing sword",      2,  400,    Card_item::ItemType::NONE       )); // TODO: not for thiefs
    //    std::random_shuffle(treasure_deck.begin(), treasure_deck.end());
}
Deck::~Deck()
{
//    std::vector<std::vector<Card_base*> > decks(4);// = { door_deck, door_deck_used, treasure_deck, treasure_deck_used };
//    for (auto& a : door_deck)
//        decks.at(0).push_back(a);
//    for (auto& a : door_deck_used)
//        decks.at(1).push_back(a);
//    for (auto& a : treasure_deck)
//        decks.at(2).push_back(a);
//    for (auto& a : treasure_deck_used)
//        decks.at(3).push_back(a);
//    for (auto& deck : decks)
//    {
//        for (auto& card : deck)
//            delete card;
//        deck.clear();
//    }
}

Card_monster* Deck::pullDoorCard()
{
    if (door_deck.empty())
    {
        reshuffleDoorCards(); // try reshuffle
        if (door_deck.empty())
        {
            Logger::getLogger()->log(LogType::ERROR, "Door deck is empty, can not draw door cards!");
            return nullptr;
        }
    }
    Card_monster* card = door_deck.back();
    door_deck.pop_back();

    Logger::getLogger()->log(LogType::INFO, "Drawed door card name: " + card->cardName);

    return card;
}
Card_item* Deck::pullTreasureCard()
{
    if (treasure_deck.empty())
    {
        reshuffleTreasureCards(); // try reshuffle
        if (treasure_deck.empty())
        {
            Logger::getLogger()->log(LogType::ERROR, "Treasure deck is empty, can not draw treasure cards!");
            return nullptr;
        }
    }
    Card_item* card = treasure_deck.back();
    treasure_deck.pop_back();

    Logger::getLogger()->log(LogType::INFO, "Drawed treasure card name: " + card->cardName);

    return card;
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


void Deck::discard(Card_base* _card)
{
    if (Card_monster* card = dynamic_cast<Card_monster*>(_card))
    {
        Logger::getLogger()->log(LogType::DUMP, "Discarded door card: " + card->cardName);
        door_deck_used.push_back(card);
    }
    else if (Card_item* card = dynamic_cast<Card_item*>(_card))
    {
        Logger::getLogger()->log(LogType::DUMP, "Discarded treasure card: " + card->cardName);
        treasure_deck_used.push_back(card);
    }
    else
        Logger::getLogger()->log(LogType::FATAL, "Unknown discarded card type.");
}
