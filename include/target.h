#ifndef TARGET_H
#define TARGET_H

#include <string>

class Target
{
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
