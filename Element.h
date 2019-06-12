#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

using std::string;

class Element
{
    public:
        Element();
        virtual ~Element();
        virtual string getStrValue() const = 0;
};

#endif // ELEMENT_H
