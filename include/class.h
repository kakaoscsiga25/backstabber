#ifndef CLASS_H
#define CLASS_H


class Class
{
public:
    enum ClassType
    {
        NONE    = 0,
        CLERIC  = 1,
        THIEF   = 2,
        WARRIOR = 4,
        WIZARD  = 8,
    };

    Class(ClassType ct = ClassType::NONE) {}

    // TODO: complete the class events

    bool isWarrior() const
    {
        return class_ & ClassType::WARRIOR;
    }

    ClassType class_;
};


#endif // CLASS_H
