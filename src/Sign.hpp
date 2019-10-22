//
// Created by Denis LEWANDOWSKI on 2019-10-02.
//
#pragma once
#ifndef C__POOL_SIGN_HPP
#define C__POOL_SIGN_HPP

#include <iostream>
#include "SignOrNumber.hpp"

class Sign : public SignOrNumber {
public:

    Sign();
    Sign(char sign);

    double getValue() const override;

    bool getType() override;

    void setValue(double sign) override;

    bool    checkSign(char sign);

    bool operator==(Sign const &a) const;
    bool operator!=(Sign const &a) const;
    bool operator>(Sign const &a) const;
    bool operator<(Sign const &a) const;
    bool operator>=(Sign const &a) const;
    bool operator<=(Sign const &a) const;

    Sign &operator=(Sign const &fixed);

    ~Sign() override = default;
private:
    bool    _type; // false
    char    _sign;
    int     _priority;
    const std::string   _availableSigns;
    void    setPriotity();
};


#endif //C__POOL_SIGN_HPP
