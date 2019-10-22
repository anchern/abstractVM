#pragma once

#include <deque>
#include "Operand.hpp"
#include "Operand.cpp"
#include "Factory.hpp"
#include "Exceptions.hpp"

class VMLogic
{
public:

	void	push(eOperandType type, const std::string &value);
	void	pop();
	void	dump();
	void	assert(eOperandType type, const std::string &value);
	void	add();
	void	sub();
	void	mul();
	void	div();
	void	mod();
	void	print();
	void	exit();

	void	commandExe(const std::string &funcName);
	void	commandExe(const std::string &funcName, eOperandType type, const std::string &value);

private:
	std::deque<IOperand *>	_registers;
	static std::pair<std::string, void (VMLogic::*)()>	_funcsWithoutParams[];
    static std::pair<std::string, void (VMLogic::*)(eOperandType type, const std::string &)>	_funcsWithParams[];
    Factory _factory;
};
