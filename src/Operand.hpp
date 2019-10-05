#ifndef ABSTACTVM_OPERAND_HPP
#define ABSTACTVM_OPERAND_HPP


#include "IOperand.hpp"
#include <iomanip>
#include <cmath>
#include <sstream>

#define MAX_PRECISION 15

template <class T>
class Operand : public IOperand
{

public:
    Operand()
	{
    	_operandType = Int8;
		this->_valueString = "0";
		this->_valueScalar = 0;
	}
    explicit Operand(eOperandType operandType, T valueScalar) :
    _valueScalar(valueScalar),
    _operandType(operandType)
    {
		std::stringstream ss;

		ss << std::setprecision(MAX_PRECISION) << this->_valueScalar;
		ss >> _valueString;
	}

    explicit Operand(eOperandType operandType, std::string const &valueString) :
    _operandType(operandType)
	{
		std::stringstream ss;

		_valueScalar = std::stod(valueString);
		ss << std::setprecision(MAX_PRECISION) << this->_valueScalar;
		ss >> _valueString;
	}

    int getPrecision() const // Precision of the type of the instance
	{
    	if (_operandType < Float)
			return 0;
    	else
		{
			if (_valueString.find(".") != std::string::npos)
			{
				const std::string &tmp = _valueString.substr(_valueString.find("."));
				return tmp.size() - 1;
			}
			else
				return 0;
		}
	}
    eOperandType getType( ) const // Type of the instance
	{
		return _operandType;
	}

    IOperand const * operator+( IOperand const & rhs ) const // Sum
	{

	}
    IOperand const * operator-( IOperand const & rhs ) const // Difference
	{
		return nullptr;
	}
    IOperand const * operator*( IOperand const & rhs ) const // Product
	{
		return nullptr;
	}
    IOperand const * operator/( IOperand const & rhs ) const // Quotient
	{
		return nullptr;
	}
    IOperand const * operator%( IOperand const & rhs ) const // Modulo
	{
		return nullptr;
	}

    std::string const &toString() const
	{
		return _valueString;

	}

	~Operand()
	{

	};

private:
    T				_valueScalar;
    eOperandType	_operandType;
    std::string		_valueString;
};


#endif
