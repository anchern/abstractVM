#include "Operand.hpp"

class Factory;

namespace
{	template <class T>
	bool checkOverflow(std::string const &number)
	{
		std::string max = std::to_string(std::numeric_limits<T>::max());
		std::cout << number.compare(max) << std::endl;
		return true;
	}
}

template <class T>
Operand<T>::Operand()
{
	_operandType = Int8;
	this->_valueString = "0";
	this->_valueScalar = 0;
}

template <class T>
Operand<T>::Operand(eOperandType operandType, T valueScalar) :
		_valueScalar(valueScalar),
		_operandType(operandType)
{
	std::stringstream ss;
	double convert;

	if (_operandType == Int8)
		ss << static_cast<int>(this->_valueScalar);
	else
		ss << std::setprecision(MAX_PRECISION) << this->_valueScalar;
	ss >> _valueString;
	ss >> convert;
	if (_operandType < Float && _valueScalar != static_cast<long>(convert))
		throw (std::logic_error("Hyu"));
}

template <class T>
Operand<T>::Operand(eOperandType operandType, std::string const &valueString) :
		_operandType(operandType)
{
	std::stringstream ss;
	double convert;

//	checkOverflow<T>("10");
	try
	{
		if (_operandType == Float)
			convert = std::stof(valueString);
		else
			convert = std::stod(valueString);
	}
	catch (...)
	{
		throw (std::logic_error("!!!!Hyu!!!"));
	}
	_valueScalar = convert;
	if (_operandType < Float && _valueScalar != static_cast<long>(convert))
		throw (std::logic_error("Hyu!!!"));
	else if (convert == INFINITY)
		throw (std::logic_error("Hyu!"));
	if (_operandType == Int8)
		ss << static_cast<int>(this->_valueScalar);
	else
		ss << std::setprecision(MAX_PRECISION) << this->_valueScalar;
	ss >> _valueString;

}

template <class T>
int	Operand<T>::getPrecision() const
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

template <class T>
T Operand<T>::getValueScalar() const
{
    return _valueScalar;
}

template <class T>
eOperandType	Operand<T>::getType() const
{
	return _operandType;
}

template <class T>
std::string const	&Operand<T>::toString() const
{
	return _valueString;
}

template<class K>
void check_adding(K a, K b)
{
    K sum = a + b;
    if ((a < 0) == (b < 0)) {
        if (a < 0 && sum > b)
            throw std::logic_error("Underflow");
        else if (sum < b)
            throw std::logic_error("Overflow");
    }
}

template<class T> void
check_mul(T a, T b)
{
    T max = std::numeric_limits<T>::max();
    T abs_a = (a < 0 ? a * -1 : a);
    T abs_b = (b < 0 ? b * -1 : b);
    if (abs_a > max/abs_b) {
        if ((a < 0) && (b < 0))
            throw std::logic_error("Overflow");
        else if ((a > 0) && (b > 0))
            throw std::logic_error("Overflow");
        else
            throw std::logic_error("Underflow");
    }
}

template <class T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const
{

	const IOperand *returned;
	double v1 = 0, v2 = 0;
	std::stringstream ssv1, ssv2, res;

	ssv1 << rhs.toString();
	ssv1 >> v1;
	ssv2 << this->toString();
	ssv2 >> v2;
	check_adding(v1, v2);
	res << v1 + v2;
	if (rhs.getType() > this->_operandType)
		returned = Factory().createOperand(rhs.getType(), res.str());
	else
		returned = Factory().createOperand(_operandType, res.str());
	return (returned);

}

template <class T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const
{
	const IOperand *returned;
	double v1 = 0, v2 = 0;
	std::stringstream ssv1, ssv2, res;

	ssv1 << rhs.toString();
	ssv1 >> v1;
	ssv2 << this->toString();
	ssv2 >> v2;
    check_adding(v2, -v1);
    res << v2 - v1;
	if (rhs.getType() > this->_operandType)
		returned = Factory().createOperand(rhs.getType(), res.str());
	else
		returned = Factory().createOperand(_operandType, res.str());
	return (returned);
}

template <class T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
	const IOperand *returned;
	double v1 = 0, v2 = 0;
	std::stringstream ssv1, ssv2, res;

	ssv1 << rhs.toString();
	ssv1 >> v1;
	ssv2 << this->toString();
	ssv2 >> v2;
	check_mul(v1, v2);
	res << v1 * v2;
	if (rhs.getType() > this->_operandType)
		returned = Factory().createOperand(rhs.getType(), res.str());
	else
		returned = Factory().createOperand(_operandType, res.str());
	return (returned);
}

template <class T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
	const IOperand *returned;
	double v1 = 0, v2 = 0;
	std::stringstream ssv1, ssv2, res;

	ssv1 << rhs.toString();
	ssv1 >> v1;
	ssv2 << this->toString();
	ssv2 >> v2;
	if (v2 == 0)
	    throw (std::logic_error("Cant divide by zero"));
    check_mul(v2, 1 / v1);
    res << v2 / v1;
	if (rhs.getType() > this->_operandType)
		returned = Factory().createOperand(rhs.getType(), res.str());
	else
		returned = Factory().createOperand(_operandType, res.str());
	return (returned);
}

template <class T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
	eOperandType rhsType, thisType;

	rhsType = rhs.getType();
	thisType = _operandType;
	if (rhsType != Double && rhsType != Float && thisType != Double && thisType != Float)
	{
		const IOperand *returned;
		int v1 = 0, v2 = 0;
		std::stringstream ssv1, ssv2, res;

		ssv1 << rhs.toString();
		ssv1 >> v1;
		ssv2 << this->toString();
		ssv2 >> v2;
        if (v2 == 0)
            throw (std::logic_error("Cant modulo by zero"));
		res << v2 % v1;
		if (rhs.getType() > _operandType)
			returned = Factory().createOperand(rhs.getType(), res.str());
		else
			returned = Factory().createOperand(_operandType, res.str());
		return (returned);
	}
	else
		throw (std::logic_error("Urod"));
}



template <class T>
Operand<T>::~Operand()
{}
