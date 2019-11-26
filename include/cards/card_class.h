#ifndef CARD_CLASS_H
#define CARD_CLASS_H

#include "card_base.h"
#include "class.h"
#include "logger.h"


class Card_class : public Card_base
{
public:
    Card_class(std::string ID, std::string name) : Card_base(ID, name)
    {
        if (name == "Cleric")
            classType = Class::ClassType::CLERIC;
        else if (name == "Thief")
            classType = Class::ClassType::THIEF;
        else if (name == "Warrior")
            classType = Class::ClassType::WARRIOR;
        else if (name == "Wizard")
            classType = Class::ClassType::WIZARD;
        else
            Logger::getLogger()->log(LogType::FATAL, "UNKNOWN CLASS TYPE: " + name);
    }

    Class::ClassType classType;
};

#endif // CARD_CLASS_H
