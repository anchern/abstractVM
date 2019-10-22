
#pragma once

#include "stack"
#include "string"
#include "Sign.hpp"
#include "Number.hpp"
#include <cmath>


class Calculator {
public:
    Calculator() = default;

    double    calculatePolishString(std::string &string);

private:
    std::vector<SignOrNumber *> createPolishString(std::string &input);
};


