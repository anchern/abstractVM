#ifndef ABSTRACTVM_FACTORY_HPP
#define ABSTRACTVM_FACTORY_HPP

#include "../inc/abstractVmIncs.hpp"
#include "Operand.hpp"

class Factory
{
public:
	Factory() = default;

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	~Factory() = default;

private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

private:
	static std::pair<
				eOperandType,
				IOperand const *(Factory::*)( std::string const & value ) const
	        > _createFunctions[];
};


#endif
