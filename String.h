#ifndef STRING_H
#define STRING_H

#include "Element.h"
#include <string>

using std::string;

class String : public Element
{
    private:
        string value;

    public:
        String(const string value);

        string getStrValue() const;
};

#endif // STRING_H
