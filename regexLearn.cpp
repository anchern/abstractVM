#include <iostream>
#include <regex>
#include <string>

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
		return (res);

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

int main(int argc, char** argv)
{
	try
	{
		std::string str = "push int8( -4 + ( 8   *(384 / 5)- +98 ) )";
//		std::string str = "push int8( 4 )";
		std::cmatch result;
		std::regex regular(makeRegexStr(true));

		if (std::regex_match(str.c_str(), result, regular))
			std::cout << "true" << std::endl;
		else
			std::cout << "false" << std::endl;

	for (auto i : result)
		std::cout << i << std::endl;
//		std::cout << result[0] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}