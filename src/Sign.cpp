
#include "Sign.hpp"

Sign::Sign() : _availableSigns("+-*/()^")
{
    _sign = '!';
    _type = false;
}

Sign::Sign(char sign) : _availableSigns("+-*/()^")
{
    _type = false;
    if (checkSign(sign))
        _sign = sign;
    else
        _sign = '!';
    setPriotity();
}

Sign& Sign::operator=(Sign const &fixed)
{
    if (this != &fixed)
    {
       _sign = fixed._sign;
        _priority = fixed._priority;
    }
    return (*this);
}

bool Sign::checkSign(char sign)
{
    for (char _availableSign : _availableSigns)
    {
        if (sign == _availableSign)
            return true;
    }
    return (false);
}

double Sign::getValue() const
{
    return _sign;
}

bool Sign::getType()
{
    return _type;
}

void Sign::setValue(double sign)
{
    sign = static_cast<char>(sign);
    if (checkSign(static_cast<char>(sign)))
        _sign = static_cast<char>(sign);
    else
        _sign = '?';
    setPriotity();
}

void Sign::setPriotity()
{
    if (_sign == '(' || _sign == ')')
        _priority = 0;
    if (_sign == '+' || _sign == '-')
        _priority = 1;
    if (_sign == '/' || _sign == '*')
        _priority = 2;
    if (_sign == '^')
        _priority = 3;
}


bool Sign::operator==(Sign const &a) const
{
    return (this->_priority == a._priority);
}
bool Sign::operator!=(Sign const &a) const
{
    return (this->_priority != a._priority);
}
bool Sign::operator>(Sign const &a) const
{
    return (this->_priority > a._priority);
}
bool Sign::operator<(Sign const &a) const
{
    return (this->_priority < a._priority);
}
bool Sign::operator>=(Sign const &a) const
{
    return (this->_priority >= a._priority);
}
bool Sign::operator<=(Sign const &a) const
{
    return (this->_priority <= a._priority);
}
