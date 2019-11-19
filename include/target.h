#ifndef TARGET_H
#define TARGET_H

#include <string>
#include <iostream>
#include <QObject>

class Target : public QObject
{
    Q_OBJECT
public:
    Target(std::string name, int level) : name(name), level(level) {}
    virtual ~Target() {}

    std::string getName() const { return name; }

    int getAttackPower() const { return level; }


protected:
    std::string name;
    int level;
};


#endif // TARGET_H
