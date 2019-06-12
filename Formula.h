#ifndef FORMULA_H
#define FORMULA_H

#include "Element.h"
#include <string>

using  std::string;

class Formula : public Element
{
    private:
        string value;

    public:
        Formula(string value);

        string getStrValue() const;
};

#endif // FORMULA_H
