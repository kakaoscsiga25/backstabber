#ifndef CARD_RACE_H
#define CARD_RACE_H

#include "card_base.h"
#include "race.h"
#include "logger.h"


class Card_race : public Card_base
{
public:
    Card_race(std::string name) : Card_base(name)
    {
        if (name == "Dwarf")
            raceType = Race::RaceType::DWARF;
        else if (name == "Elf")
            raceType = Race::RaceType::ELF;
        else if (name == "Halfling")
            raceType = Race::RaceType::HALFLING;
        else if (name == "Orc")
            raceType = Race::RaceType::ORC;
        else
            Logger::getLogger()->log(LogType::FATAL, "UNKNOWN RACE TYPE: " + name);
    }

    Race::RaceType raceType;
};

#endif // CARD_RACE_H
