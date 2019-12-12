#ifndef CLASS_H
#define CLASS_H


class Class
{
public:
    enum ClassType
    {
        UNKNOWN         = 0,
        NONE            = 1,
        CLERIC          = 2,
        THIEF           = 4,
        WARRIOR         = 8,
        WIZARD          = 16,

        ALL             = NONE | CLERIC | THIEF | WARRIOR | WIZARD,

        EXCEPT_CLERIC   = ALL - CLERIC,
        EXCEPT_THIEF    = ALL - THIEF,
        EXCEPT_WARRIOR  = ALL - WARRIOR,
        EXCEPT_WIZARD   = ALL - WIZARD,
    };

    Class(ClassType ct = ClassType::NONE) {}



    bool is(const ClassType& cl) const
    {
        return class_ & cl;
    }
    bool isNot(const ClassType& cl) const
    {
        return !(class_ & cl);
    }

    ClassType class_;
};


#endif // CLASS_H
