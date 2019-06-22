#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "IOperand.hpp"

class OperandFactory
{
private:
	IOperand const *(OperandFactory::*_FunctionTable[5])(std::string const &)const;

	IOperand const *createInt8(std::string const &value) const;
	IOperand const *createInt16(std::string const &value) const;
	IOperand const *createInt32(std::string const &value) const;
	IOperand const *createFloat(std::string const &value) const;
	IOperand const *createDouble(std::string const &value) const;

public:
	OperandFactory();
	~OperandFactory();
	IOperand const *createOperand(eOperandType type, std::string const &value) const;
};

#endif
