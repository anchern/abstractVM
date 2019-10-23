#pragma once

#include <deque>
#include "Operand.hpp"
#include "Operand.cpp"
#include "Factory.hpp"
#include "Exceptions.hpp"

class VMLogic
{
public:

    VMLogic();

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

	bool    getIsExitPresent() const;

private:
	std::deque<IOperand *>	_registers;
	static std::pair<std::string, void (VMLogic::*)()>	_funcsWithoutParams[];
    static std::pair<std::string, void (VMLogic::*)(eOperandType type, const std::string &)>	_funcsWithParams[];
private:
    Factory _factory;
    bool    _isExitPresent;
};
