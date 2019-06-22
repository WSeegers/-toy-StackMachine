#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <string>

enum eOperandType
{
	_int8,
	_int16,
	_int32,
	_float,
	_double
};

class IOperand
{
public:
	virtual int getPrecision(void) const = 0;
	virtual eOperandType getType(void) const = 0;
	virtual IOperand const *operator+(IOperand const &rhs) const = 0;
	virtual IOperand const *operator-(IOperand const &rhs) const = 0;
	virtual IOperand const *operator*(IOperand const &rhs) const = 0;
	virtual IOperand const *operator/(IOperand const &rhs) const = 0;
	virtual IOperand const *operator%(IOperand const &rhs) const = 0;
	virtual bool operator==(IOperand const &rhs) const = 0;
	virtual std::string const &toString(void) const = 0;
	virtual ~IOperand(void) {}
};

#endif
