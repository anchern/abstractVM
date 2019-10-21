#include <iostream>
#include <regex>
#include <string>
#include <limits>
#include <stack>
#include <sstream>
#include <cmath>
#include "src/Sign.hpp"
#include "src/Number.hpp"
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

bool isDigit(char r)
{
    return r >= '0' && r <= '9';
}

std::string getNumber(std::string &input, int i)
{
    std::string result;

    while ((isDigit(input[i]) == 1 || input[i] == '.') && input[i] != ' ' &&  i < input.length())
    {
        result += input[i];
        i++;
    }
    return  result;
}

void    printWithExit(const std::string &string)
{
    std::cout << string << std::endl;
    exit(0);
}

template <class T>
void    stackPop(std::stack<T> &stack)
{
    if (!stack.empty())
        stack.pop();
    else
        printWithExit("Seems you try to crash me)");
}

template <class T>
T stackTop(std::stack<T> &stack)
{
    if (!stack.empty())
        return stack.top();
    else
        printWithExit("Seems you try to crash me)");
    return stack.top();
}

void    vectorPopBack(std::vector<SignOrNumber *> &input)
{
    if (!input.empty())
        input.pop_back();
    else
        printWithExit("Seems you try to crash me)");
}


int checkSignedNumber(std::string &input, int i)
{
    Sign sign;
    int j;

    j = i;
    if (input[j] == ')' || input[j] == '(')
        return 2;
    if (i > 0)
        i--;
    while (i > 0 && input[i] == ' ')
        i--;
    if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
    {
        if (j + 1 < input.size() && isdigit(input[j + 1]))
        {
            if (input[j] == '+' || input[j] == '-')
                return 1;
            return 0;
        }
        return 0;
    }
    return 2;
}

std::vector<SignOrNumber *> createPolishString(std::string &input)
{
    std::stack<SignOrNumber *> mainStack;
    std::stack<SignOrNumber *> operandStack;
    std::vector<SignOrNumber *> result;
    SignOrNumber *tmpString = nullptr;
    SignOrNumber *topString = nullptr;
    Sign *sign1 = nullptr;
    Sign sign2;
    size_t kek;

	try
	{
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] == ')')
			{
				topString = stackTop(operandStack);
				while (topString->getValue() != '(')
				{
					mainStack.push(topString);
					stackPop(operandStack);
					topString = stackTop(operandStack);
				}
				stackPop(operandStack);
				continue;
			}
			if (sign2.checkSign(input[i]))
			{
				if (checkSignedNumber(input, i) == 1)
				{
					mainStack.push(
							new Number(std::stod(input.c_str() + i, &kek)));
					i++;
					while ((isdigit(input[i]) == 1 || input[i] == '.') &&
						   input[i] != ' ' && i < input.length())
					{
						i++;
					}
					if (input[i] != ' ')
						i--;
					continue;
				} else if (checkSignedNumber(input, i) == 0)
					exit(2);
				if (!operandStack.empty())
				{
					tmpString = stackTop(operandStack);
					sign1 = dynamic_cast<Sign *>(tmpString);
					sign2.setValue(input[i]);
					if (sign2 <= *sign1 && input[i] != '(')
					{
						mainStack.push(tmpString);
						stackPop(operandStack);
					}
				}
				sign1 = new Sign(input[i]);
				operandStack.push(static_cast<SignOrNumber *>(sign1));
				continue;
			}
			if (input[i] == ' ')
				continue;
			if (isdigit(input[i]))
			{
				mainStack.push(new Number(std::stod(input.c_str() + i, &kek)));
				while ((isdigit(input[i]) == 1 || input[i] == '.') &&
					   input[i] != ' ' && i < input.length())
				{
					i++;
				}
				if (input[i] != ' ')
					i--;
			}
		}
		while (!operandStack.empty())
		{
			mainStack.push(operandStack.top());
			operandStack.pop();
		}
		while (!mainStack.empty())
		{
			result.push_back(mainStack.top());
			mainStack.pop();
		}
		return result;
	}
	catch (...)
	{
		throw (std::logic_error("overflow"));
	}
}

double   returnRightFixed(const double &number1, const double &number2, char sign)
{
    if (sign == '^')
        return pow(number1, number2);
    if (sign == '+')
        return number1 + number2;
    if (sign == '-')
        return number2 - number1;
    if (sign == '*')
        return number1 * number2;
    if (sign == '/')
    {
        if (number1 == double(0))
        {
            std::cout << "CANT DIVIDE BY 0!" << std::endl;
            exit(0);
        }
        return number2 / number1;
    }
}

double    calculatePolishString(std::vector<SignOrNumber *> &input)
{
    std::stack<double > mainStack;
    double  tmp1;
    double  tmp2;
    Sign sign1;

    while (!input.empty())
    {
        if (!input[input.size() - 1]->getType())
        {
            tmp1 = stackTop(mainStack);
            stackPop(mainStack);
            tmp2 = stackTop(mainStack);
            stackPop(mainStack);
            mainStack.push(returnRightFixed(tmp1, tmp2, static_cast<char>(input[input.size() - 1]->getValue())));
            vectorPopBack(input);
            continue;
        }
        if (input[input.size() - 1]->getType())
        {
            mainStack.push(input[input.size() - 1]->getValue());
            vectorPopBack(input);
        }
    }
    return stackTop(mainStack);
}

int main(int argc, char *argv[])
{

    std::string string;
    std::vector<SignOrNumber *> a;

	try
	{
		std::string str;
//		std::string str = "pop int8( -4 + ( 8   *(384 / 5)- +98 ) )";
//		std::string str = "push int8( 4 )";
		std::cmatch result;
		std::regex regularWithArg(makeRegexStr(true));
		std::regex regular(makeRegexStr(false));
		std::regex commentRegular("\\s*(;[\\d\\D]*)?");
		std::ifstream file(argv[1]);

		std::string command;
		std::string type;
		std::string value;
		std::string comment;

		VMLogic vmLogic;

		std::stringstream ss;

		if (argc < 2)
		{
			std::cout << "Hyu" << std::endl;
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
				a = createPolishString(value);
				ss << std::setprecision(7) << calculatePolishString(a);
				vmLogic.commandExe(command, getType(type), ss.str());
				ss.str("");
//				std::cout << "////////////////////////////////////" << std::endl;
//				std::cout << calculatePolishString(a) << std::endl;
//				std::cout << "////////////////////////////////////" << std::endl;
			}
			else if (std::regex_match(str.c_str(), result, regular))
			{
//				std::cout << "Is command without argument" << std::endl;
				command = result[1];
				if (std::string(result[result.size() - 1])[0] == ';')
					comment = result[result.size() - 1];
				vmLogic.commandExe(command);
			}
			command = "";
			type = "";
			value = "";
//			else if (std::regex_match(str.c_str(), result, commentRegular))
//				std::cout << "Is space or comment" << std::endl;
//			else
//				std::cout << "false" << std::endl;
//			std::cout << "++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
//			for (auto i : result)
//				std::cout << i << std::endl;
//			std::cout << "++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
//			std::cout << comment << std::endl;
//			std::cout << "++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		}


//		std::cout << result[0] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

//    if (argc == 2)
//    {
//        string = argv[1];
//        a = createPolishString(string);
//        std::cout << calculatePolishString(a) << std::endl;
//    }
//    else
//        printWithExit("Illegal number of arguments, try more");
}