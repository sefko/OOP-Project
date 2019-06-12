#include "Fraction.h"
#include <iostream>

Fraction::Fraction(const double value) : value(value)
{

}

string Fraction::getStrValue() const
{
    string temp = std::to_string(value);
    int tempSize = temp.length();
    bool isDotFound = false;

    if(temp.find('.') != string::npos)
    {
        while((temp[tempSize - 1] == '0' || temp[tempSize - 1] == '.') && !isDotFound)
        {
        if(temp[tempSize - 1] == '.')
            isDotFound = true;
        temp.erase(temp.end() - 1);
        --tempSize;
        }
    }

    return temp;
}
