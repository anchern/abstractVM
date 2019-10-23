#include "VMLogic.hpp"

namespace
{
    template <class T>
    void printGreen(T value)
    {
        std::cout.precision(4);
        std::cout  <<  "\033[1;32m" <<  value << "\033[0m" << std::endl;
    }
}

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

std::pair<std::string, void (VMLogic::*)(eOperandType type, const std::string &)>
        VMLogic::_funcsWithParams[] = {{"push", &VMLogic::push},
                                       {"assert", &VMLogic::assert}

};

VMLogic::VMLogic()
{
    _isExitPresent = false;
}

void VMLogic::commandExe(const std::string &funcName)
{
	for (auto & _funcWithoutParams : _funcsWithoutParams)
	{
		if (_funcWithoutParams.first == funcName)
		{
			(this->*_funcWithoutParams.second)();
			return ;
		}
	}
}

void VMLogic:: commandExe(const std::string &funcName, eOperandType type, const std::string &value)
{
	for (auto & _funcWithParams : _funcsWithParams)
	{
		if (_funcWithParams.first == funcName)
		{
			(this->*_funcWithParams.second)(type, value);
			return ;
		}
	}
}

void VMLogic::push(eOperandType type, const std::string &value)
{
    _registers.push_front(const_cast<IOperand *>(_factory.createOperand(type, value)));
}

void VMLogic::pop()
{
    if (!_registers.empty())
        _registers.pop_front();
    else
        throw Exceptions::StackIsEmpty();
}

void VMLogic::dump()
{
    for (auto & _register : _registers)
        printGreen(_register->toString());
}

void VMLogic::assert(eOperandType type, const std::string &value)
{
    IOperand const *tmp = _factory.createOperand(type, value);

    if ((*_registers.begin())->toString() != tmp->toString())
    {
        delete tmp;
        throw std::logic_error("Assert error. Values is not equal");
    }
    delete tmp;
}

void VMLogic::add()
{
    IOperand const *result;

    if (_registers.size() < 2)
        throw Exceptions::StackHasLessTwoElements();
    result = *(*_registers.begin()) + *(*(++_registers.begin()));
    _registers.pop_front();
    _registers.pop_front();
    _registers.push_front(const_cast<IOperand *>(result));
}

void VMLogic::sub()
{
    IOperand const *result;

    if (_registers.size() < 2)
        throw Exceptions::StackHasLessTwoElements();
    result = *(*_registers.begin()) - *(*(++_registers.begin()));
    _registers.pop_front();
    _registers.pop_front();
    _registers.push_front(const_cast<IOperand *>(result));
}

void VMLogic::mul()
{
    IOperand const *result;

    if (_registers.size() < 2)
        throw Exceptions::StackHasLessTwoElements();
    result = *(*_registers.begin()) * *(*(++_registers.begin()));
    _registers.pop_front();
    _registers.pop_front();
    _registers.push_front(const_cast<IOperand *>(result));
}

void VMLogic::div()
{
    IOperand const *result;

    if (_registers.size() < 2)
        throw Exceptions::StackHasLessTwoElements();
    result = *(*++_registers.begin()) / *(*(_registers.begin()));
    _registers.pop_front();
    _registers.pop_front();
    _registers.push_front(const_cast<IOperand *>(result));
}

void VMLogic::mod()
{
    IOperand const *result;

    if (_registers.size() < 2)
        throw Exceptions::StackHasLessTwoElements();
    result = *(*++_registers.begin()) % *(*(_registers.begin()));
    _registers.pop_front();
    _registers.pop_front();
    _registers.push_front(const_cast<IOperand *>(result));
}

void VMLogic::print()
{
    if (_registers.empty())
        throw Exceptions::StackIsEmpty();
    if ((*_registers.begin())->getType() == Int8)
        printGreen(static_cast<char>(Operand<char>(Int8, (*_registers.begin())->toString()).getValueScalar()));
    else
        throw std::logic_error("Print error.Value is not an 8-bit integer");
}

void VMLogic::exit()
{
    _isExitPresent = true;
}

bool VMLogic::getIsExitPresent() const
{
    return _isExitPresent;
}
