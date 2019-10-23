
#pragma once

class SignOrNumber
{
public:
    virtual  bool   getType() = 0;
    virtual double  getValue() const = 0;
    virtual void    setValue(double value) = 0;
    virtual  ~SignOrNumber() = default;
private:
};