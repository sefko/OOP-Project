#ifndef INTEGER_H
#define INTEGER_H

#include "Element.h"


class Integer : public Element
{
    private:
        int value;

    public:
        Integer(const int value);

        string getStrValue() const;
};

#endif // INTEGER_H
