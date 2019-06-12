#include "Integer.h"
#include <iostream>

Integer::Integer(const int value) : value(value)
{

}

string Integer::getStrValue() const
{
    return std::to_string(value);
}
