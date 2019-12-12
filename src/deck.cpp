#include "deck.hpp"
#include "cards/card_monster.h"
#include "cards/card_item.h"
#include "logger.h"

Deck::Deck()
{
    // Initialize doors deck
    door_deck.push_back(new Card_monster("DMO_MO_01",    "Squidzilla", 18, 4, 2, Monster::BadStuffs::DIE));
    door_deck.push_back(new Card_monster("DMO_MO_02",    "Plutonium dragon", 20, 5, 2, Monster::BadStuffs::DIE));
    door_deck.push_back(new Card_monster("DMO_MO_03",    "Large angry chicken", 2, 1, 1, Monster::BadStuffs::LOSE_LVL));
    std::random_shuffle(door_deck.begin(), door_deck.end());

    treasure_deck.push_back(new Card_item("DMO_TI_01",   "Spiky knee\'s",                  1,  200,    Card_item::ItemType::NONE       , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_02",   "Eleven-foot pole",               1,  200,    Card_item::ItemType::TWO_HAND   , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_03",   "Rat on a stick",                 1,  0,      Card_item::ItemType::ONE_HAND   , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_04",   "Helm of courage",                1,  200,    Card_item::ItemType::HEAD       , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_05",   "Hireling",                       1,  0,      Card_item::ItemType::NONE       , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_06",   "Horny helmet",                   1,  600,    Card_item::ItemType::HEAD       , false, Class::ClassType::ALL           )); // TODO: +3 if elf
    treasure_deck.push_back(new Card_item("DMO_TI_07",   "Slimy armor",                    1,  200,    Card_item::ItemType::ARMOR      , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_08",   "Leather armor",                  1,  300,    Card_item::ItemType::ARMOR      , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_09",   "Buckler of swashing",            2,  400,    Card_item::ItemType::ONE_HAND   , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_10",   "Dancing sword",                  2,  400,    Card_item::ItemType::NONE       , false, Class::ClassType::EXCEPT_THIEF  ));
    treasure_deck.push_back(new Card_item("DMO_TI_20",   "Boots of butt-kicking",          2,  400,    Card_item::ItemType::FOOT       , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_11",   "Flaming armor",                  2,  400,    Card_item::ItemType::ARMOR      , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_12",   "Sneaky bastard sword",           2,  400,    Card_item::ItemType::ONE_HAND   , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_13",   "Lamburger and anchovy sandwich", 3,  100,    Card_item::ItemType::NONE       , false, Class::ClassType::ALL           )); // TODO: only for halfling
    treasure_deck.push_back(new Card_item("DMO_TI_14",   "Stepladder",                     3,  400,    Card_item::ItemType::NONE       , true , Class::ClassType::ALL           )); // TODO: only for halfling
    treasure_deck.push_back(new Card_item("DMO_TI_15",   "Really impressive title",        3,  0,      Card_item::ItemType::NONE       , false, Class::ClassType::ALL           ));
    treasure_deck.push_back(new Card_item("DMO_TI_16",   "Pantyhose of giant strength",    3,  600,    Card_item::ItemType::NONE       , false, Class::ClassType::EXCEPT_WARRIOR));
    treasure_deck.push_back(new Card_item("DMO_TI_17",   "Pointy hat of power",            3,  400,    Card_item::ItemType::HEAD       , false, Class::ClassType::WIZARD        ));
    treasure_deck.push_back(new Card_item("DMO_TI_18",   "Bad-ass bandana",                3,  400,    Card_item::ItemType::HEAD       , false, Class::ClassType::ALL           )); // TODO: only for humans
    treasure_deck.push_back(new Card_item("DMO_TI_19",   "Mithril armor",                  3,  600,    Card_item::ItemType::ARMOR      , true , Class::ClassType::EXCEPT_WIZARD ));
    std::random_shuffle(treasure_deck.begin(), treasure_deck.end());
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
    Logger::getLogger()->log(LogType::INFO, "Door card\'s deck is resuffled: " + std::to_string(door_deck.size()));
}
void Deck::reshuffleTreasureCards()
{
    treasure_deck.insert(treasure_deck.end(), treasure_deck_used.begin(), treasure_deck_used.end());
    treasure_deck_used.clear();
    std::random_shuffle(treasure_deck.begin(), treasure_deck.end());
    Logger::getLogger()->log(LogType::INFO, "Treasure card\'s deck is resuffled: " + std::to_string(treasure_deck.size()));
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
