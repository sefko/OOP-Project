#ifndef EMPTYSPACE_H
#define EMPTYSPACE_H

#include "Element.h"


class EmptySpace : public Element
{
    public:
        EmptySpace();

        string getStrValue() const;
};

#endif // EMPTYSPACE_H
