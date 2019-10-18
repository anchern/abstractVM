#include "Factory.hpp"
#include "Operand.cpp"

std::pair<
		eOperandType,
		IOperand const *(Factory::*)( std::string const & value ) const
> Factory::_createFunctions[] = {
		{Int8, &Factory::createInt8},
		{Int16, &Factory::createInt16},
		{Int32, &Factory::createInt32},
		{Float, &Factory::createFloat},
		{Double, &Factory::createDouble}
};

IOperand const *
Factory::createOperand(eOperandType type, std::string const &value) const
{
	for (auto func : _createFunctions)
	{
		if (func.first == type)
			return (this->*func.second)(value);
	}
	return nullptr;
}

IOperand const *Factory::createInt8(std::string const &value) const
{
	return dynamic_cast<IOperand const *>(new Operand<int8_t>(Int8, value));
}

IOperand const *Factory::createInt16(std::string const &value) const
{
	return dynamic_cast<IOperand const *>(new Operand<int16_t>(Int16, value));
}

IOperand const *Factory::createInt32(std::string const &value) const
{
	return dynamic_cast<IOperand const *>(new Operand<int32_t>(Int32, value));
}

IOperand const *Factory::createFloat(std::string const &value) const
{
	return dynamic_cast<IOperand const *>(new Operand<float>(Float, value));
}

IOperand const *Factory::createDouble(std::string const &value) const
{
	return dynamic_cast<IOperand const *>(new Operand<double >(Double, value));
}

