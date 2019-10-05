#include <iostream>
#include "Operand.hpp"
#include "Factory.hpp"

int main()
{
	Factory factory;
	IOperand const *operand = factory.createOperand(Double, "50.88");
	std::cout << operand->toString() << std::endl;
	std::cout << operand->getPrecision() << std::endl;
	std::cout << operand->getType() << std::endl;

	return 0;
}