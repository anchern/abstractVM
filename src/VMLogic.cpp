#include "VMLogic.hpp"


std::pair<std::string, void (VMLogic::*)()> VMLogic::_funcsWithoutParams[] = {
		{"pop", &VMLogic::pop},
		{"dump", &VMLogic::dump},
		{"add", &VMLogic::add},
		{"sub", &VMLogic::sub},
		{"mul", &VMLogic::mul},
		{"div", &VMLogic::div},
		{"mod", &VMLogic::mod},
		{"print", &VMLogic::print},
		{"exit", &VMLogic::exit}
};

std::pair<
			std::string,
			void (VMLogic::*)(const std::string &)
			> VMLogic::_funcsWithParams[] = {
		{"push", &VMLogic::push},
		{"assert", &VMLogic::assert}

};

void VMLogic::commandExe(const std::string &funcName)
{
	for (auto & _funcWithoutParams : _funcsWithoutParams)
	{
		if (_funcsWithoutParams->first == funcName)
			(this->*_funcWithoutParams.second)();
	}
}

void VMLogic::commandExe(const std::string &funcName, const std::string &value)
{
	for (auto & _funcWithParams : _funcsWithParams)
	{
		if (_funcsWithParams->first == funcName)
			(this->*_funcWithParams.second)(value);
	}
}
