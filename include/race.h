#ifndef RACE_H
#define RACE_H


class Race
{
public:
    enum RaceType
    {
        NONE        = 0,
        HUMAN       = 1,
        DWARF       = 2,
        ELF         = 4,
        HALFLING    = 8,
        ORC         = 16,
    };

    // TODO: write the changer things of the races

    bool isHuman() const { return race & RaceType::HUMAN; }
    bool isDwarf() const { return race & RaceType::DWARF; }
    bool isElf() const { return race & RaceType::ELF; }
    bool isHalfing() const { return race & RaceType::HALFLING; }
    bool isOrc() const { return race & RaceType::ORC; }


    RaceType race = RaceType::HUMAN; // human is the default
}


#endif // RACE_H
