#include "String.h"
#include <iostream>

String::String(string value) : value(value)
{

}

string String::getStrValue() const
{
    return value;
}
