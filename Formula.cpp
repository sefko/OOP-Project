#include "Formula.h"
#include <iostream>

Formula::Formula(string value) : value(value)
{

}

string Formula::getStrValue() const
{
    return value;
}
