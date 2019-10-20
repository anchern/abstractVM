#pragma once

#include <deque>
#include "Operand.hpp"
#include "Operand.cpp"
#include "Factory.hpp"

class VMLogic
{
public:

    class StackIsEmpty : public std::exception
    {
    public:
        virtual const char    *what() const throw();
    };

    class StackHasLessTwoElements : public std::exception
    {
    public:
        virtual const char    *what() const throw();
    };

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
