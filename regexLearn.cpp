#include <iostream>
#include <regex>
#include <string>
#include <limits>
#include <stack>
#include <sstream>
#include <cmath>
#include "src/Sign.hpp"
#include "src/Number.hpp"
#include "src/Calculator.hpp"
#include <fstream>
#include "src/VMLogic.hpp"

namespace {

	std::string commands[] = {
			"pop",
			"dump",
			"add",
			"sub",
			"mul",
			"div",
			"mod",
			"print",
			"exit"
	};

	std::string commandsWithArgs[] = {
			"push",
			"assert"
	};

	std::string types[] = {
			"int8",
			"int16",
			"int32",
			"float",
			"double"
	};

	std::pair<std::string, eOperandType> stringType[] = {
			{"int8", Int8},
			{"int16", Int16},
			{"int32", Int32},
			{"float", Float},
			{"double", Double}
	};
}

std::string makeRegexStr(bool isCommandUseArgs)
{
	std::string res = "(";
	size_t arrSize;
	std::string spaces = "\\s*";
	std::string openBracket = "(" + spaces +"\\(" + spaces + ")*"; // NOLINT(modernize-raw-string-literal)
	std::string closeBracket = "(" + spaces +"\\)" + spaces + ")*"; // NOLINT(modernize-raw-string-literal)
	std::string number = "(" + spaces + "[\\+-]?\\d+(.\\d+)?" + spaces + ")"; // NOLINT(modernize-raw-string-literal)
	std::string	operand = "(" + spaces + "[-\\+\\*/]" + spaces + ")"; // NOLINT(modernize-raw-string-literal)
	std::string	comments = "(;[\\d\\D]*)?"; // NOLINT(modernize-raw-string-literal)

	if (isCommandUseArgs)
		arrSize = sizeof(commandsWithArgs) / sizeof(std::string);
	else
		arrSize = sizeof(commands) / sizeof(std::string);

	for (int i = 0; i < arrSize; i++)
	{
		if (isCommandUseArgs)
			res += commandsWithArgs[i];
		else
			res += commands[i];
		if (i != arrSize - 1)
			res += "|";
		else
			res += ")";
	}

	if (!isCommandUseArgs)
		return (res + spaces + comments);

	arrSize = sizeof(types) / sizeof(std::string);

	res += " (";
	for (int i = 0; i < arrSize; i++)
	{
		res += types[i];
		if (i != arrSize - 1)
			res += "|";
		else
			res += ")";

	}

	res += "\\(("+ openBracket + number + closeBracket +
		   "(" + operand + openBracket + number + closeBracket +")*)\\)" +
		   spaces + comments;
	return (res);

}

eOperandType getType(std::string const &string)
{
	for (const auto& a : stringType)
	{
		if (a.first == string)
			return (a.second);
	}
	throw (std::logic_error("stringType"));
}



int main(int argc, char *argv[])
{

    std::string string;
    std::vector<SignOrNumber *> a;
    Calculator calculator;


    try
    {
        std::string str;
        std::cmatch result;
        std::regex regularWithArg(makeRegexStr(true));
        std::regex regular(makeRegexStr(false));
        std::regex commentRegular(R"(\s*(;[\d\D]*)?)");
        std::ifstream file(argv[1]);

        std::string command;
        std::string type;
        std::string value;
        std::string comment;

        VMLogic vmLogic;

        std::stringstream ss;

        if (argc < 2)
        {
            std::cout << "Less than 2 arguments" << std::endl;
            return (0);
        }
        while (std::getline(file, str))
        {
//			std::cout << str << std::endl;
            if (std::regex_match(str.c_str(), result, regularWithArg))
            {
//				std::cout << "Is command with argument" << std::endl;
                command = result[1];
                type = result[2];
                value = result[3];
                if (std::string(result[result.size() - 1])[0] == ';')
                    comment = result[result.size() - 1];
                ss << std::setprecision(7) << calculator.calculatePolishString(value);
                vmLogic.commandExe(command, getType(type), ss.str());
                ss.str("");
            }
            else if (std::regex_match(str.c_str(), result, regular))
            {
//				std::cout << "Is command without argument" << std::endl;
                command = result[1];
                if (std::string(result[result.size() - 1])[0] == ';')
                    comment = result[result.size() - 1];
                vmLogic.commandExe(command);
            }
            else
            {
                throw std::logic_error("Invalid command");
            }
            command = "";
            type = "";
            value = "";
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

