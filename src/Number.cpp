

#include "Number.hpp"


Number::Number()
{
    _type = true;
}

Number::Number(double number)
{
    _type = true;
    _number = number;
}

bool Number::getType()
{
    return _type;
}

double Number::getValue() const
{
    return _number;
}

void Number::setValue(double value)
{
    _number = value;
}