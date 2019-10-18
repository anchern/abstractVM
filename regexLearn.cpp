#include <iostream>
#include <regex>
#include <string>

namespace {
	std::string commands[] = {
			"push",
			"pop",
			"dump",
			"assert",
			"add",
			"sub",
			"mul",
			"div",
			"mod",
			"print",
			"exit"
	};

	std::string types[] = {
			"int8",
			"int16",
			"int32",
			"float",
			"double"
	};
}

std::string makeRegexStr()
{
	std::string res = "(";
	size_t arrSize = sizeof(commands) / sizeof(std::string);

	for (int i = 0; i < arrSize; i++)
	{
		res += commands[i];
		if (i != arrSize - 1)
			res += "|";
		else
			res += ")";

	}

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


	return (res);

}

int main(int argc, char** argv)
{
	try
	{
		std::string str = "push double(54.5 / 8.08 * -6)";
		std::cmatch result;
		std::regex regular(makeRegexStr() +
						   "\\((\\+|-)?[\\d]+(.[\\d]+)?( (\\+|-|\\*|/)? (\\+|-)?[\\d]+(.[\\d]+)?)*\\)");

		if (std::regex_match(str.c_str(), result, regular))
			std::cout << "true" << std::endl;
		else
			std::cout << "false" << std::endl;

//	for (auto i : result)
//		std::cout << i << std::endl;
		std::cout << result[0] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}