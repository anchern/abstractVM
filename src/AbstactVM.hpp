#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <limits>
#include <stack>
#include <sstream>
#include <cmath>
#include "Sign.hpp"
#include "Number.hpp"
#include "Calculator.hpp"
#include <fstream>
#include "VMLogic.hpp"

class AbstactVM {

public:
    AbstactVM();

    void launch(int argc, char *argv[]);
    int  getLine();

private:
    void lexerParser(std::string &str, VMLogic &vmLogic);
    std::string makeRegexStr(int isCommandUseArgs);
    int _line;
};



