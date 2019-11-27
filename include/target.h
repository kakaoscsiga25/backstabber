#ifndef TARGET_H
#define TARGET_H

#include <string>
#include <iostream>
#include <QObject>

#include "cards/card_effect.h"


class Target : public QObject
{
    Q_OBJECT
public:
    Target(std::string name, int level) : name(name), level(level) {}
    virtual ~Target() {}

    std::string getName() const { return name; }
    int getLevel() const { return level; }

    virtual int attackPower() const { return level; }

    void addNewEffectCard(Card_effect* card) { effectCards.push_back(card); }

    int evaluateCardEffects() const
    {
        int change = 0;
        for (const auto& c : effectCards)
            change += c->changeValue;
        return change;
    }


    std::string name;
protected:
    int level;
    std::vector<Card_effect*> effectCards;
};


#endif // TARGET_H
