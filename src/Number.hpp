

#pragma once

#ifndef ABSTRACTVM_NUMBER_HPP
#define ABSTRACTVM_NUMBER_HPP


#include "SignOrNumber.hpp"

class Number : public SignOrNumber {

public:

    Number();

    Number(double number);

    bool getType() override;
    double  getValue() const override;

    void    setValue(double value) override;
    ~Number() override = default;
private:
    double  _number;
    bool    _type; //true
};


#endif //ABSTRACTVM_NUMBER_HPP
