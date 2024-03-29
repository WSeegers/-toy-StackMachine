#include "OperandFactory.hpp"
#include "Operand.hpp"

OperandFactory::OperandFactory()
{
	this->_FunctionTable[eOperandType::_int8] = &OperandFactory::createInt8;
	this->_FunctionTable[eOperandType::_int16] = &OperandFactory::createInt16;
	this->_FunctionTable[eOperandType::_int32] = &OperandFactory::createInt32;
	this->_FunctionTable[eOperandType::_float] = &OperandFactory::createFloat;
	this->_FunctionTable[eOperandType::_double] = &OperandFactory::createDouble;
}

OperandFactory::~OperandFactory() {}

IOperand const *OperandFactory::createInt8(std::string const &value) const
{
	return new Int8(value);
}

IOperand const *OperandFactory::createInt16(std::string const &value) const
{
	return new Int16(value);
}

IOperand const *OperandFactory::createInt32(std::string const &value) const
{
	return new Int32(value);
}

IOperand const *OperandFactory::createFloat(std::string const &value) const
{
	return new Float(value);
}

IOperand const *OperandFactory::createDouble(std::string const &value) const
{
	return new Double(value);
}

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
	return (this->*(_FunctionTable[type]))(value);
}

void OperandFactory::printOperand(const IOperand &op, std::ostream &os)
{
	if (op.getType() != _int8)
		throw OperandFactory::NotPrintAbleValue();
	else
		os << dynamic_cast<const Int8 &>(op).getValue();
}

const char *OperandFactory::NotPrintAbleValue ::what() const throw()
{
	return "Type of Int8 is required";
};
