#include "EmptySpace.h"
#include <iostream>

EmptySpace::EmptySpace() : Element()
{

}

string EmptySpace::getStrValue() const
{
    return " ";
}
