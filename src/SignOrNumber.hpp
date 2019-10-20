//
// Created by Denis LEWANDOWSKI on 2019-10-19.
//
#pragma once
#ifndef ABSTRACTVM_SIGNORNUMBER_HPP
#define ABSTRACTVM_SIGNORNUMBER_HPP

#endif //ABSTRACTVM_SIGNORNUMBER_HPP

class SignOrNumber
{
public:
    virtual  bool   getType() = 0;
    virtual double  getValue() const = 0;
    virtual void    setValue(double value) = 0;
    virtual  ~SignOrNumber() = default;
private:
};