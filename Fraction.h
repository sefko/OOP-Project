#ifndef FRACTION_H
#define FRACTION_H

#include "Element.h"


class Fraction : public Element
{
    private:
        double value;

    public:
        Fraction(const double value);

        string getStrValue() const;
};

#endif // FRACTION_H
