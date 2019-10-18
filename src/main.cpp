#include <iostream>
#include "Factory.hpp"

int main()
{
	std::string str = "50";
	IOperand const *operand1 = Factory().createOperand(Double, "40.555");
	IOperand const *operand2 = Factory().createOperand(Double, "5");
	std::cout << (*operand1 % *operand2)->toString() << std::endl;
	std::cout << 40.555 / 1.0 << std::endl;

	return 0;
}