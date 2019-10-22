#pragma once

#include "IOperand.hpp"
#include "Factory.hpp"
#include "Exceptions.hpp"
#include <iomanip>
#include <cmath>
#include <sstream>

#define MAX_PRECISION 15

template <class T>
class Operand : public IOperand
{

public:
	Operand();

	explicit Operand(eOperandType operandType, T valueScalar);

	explicit Operand(eOperandType operandType, std::string const &valueString);

	int getPrecision() const override; // Precision of the type of the instance

	eOperandType getType( ) const override; // Type of the instance

	T getValueScalar() const;

	IOperand const * operator+( IOperand const & rhs ) const override; // Sum

	IOperand const * operator-( IOperand const & rhs ) const override; // Difference

	IOperand const * operator*( IOperand const & rhs ) const override; // Product

	IOperand const * operator/( IOperand const & rhs ) const override; // Quotient

	IOperand const * operator%( IOperand const & rhs ) const override; // Modulo

	std::string const &toString() const override;

	~Operand() override;

private:
	T				_valueScalar;
	eOperandType	_operandType;
	std::string		_valueString;
};

