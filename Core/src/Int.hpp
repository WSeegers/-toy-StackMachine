#ifndef INT_HPP
#define INT_HPP

#include "Operand.hpp"

#include <limits>
#include <string>

template <>
Int8::Operand(const std::string &value)
		: _string(value),
			_type(eOperandType::_int8)
{
	int32_t val = std::stoi(value);
	if (val > 0 && val > std::numeric_limits<int8_t>::max())
	{
		throw Operand::Overflow();
	}
	else if (val < 0 && val < std::numeric_limits<int8_t>::min())
	{
		throw Operand::Underflow();
	}
	this->_value = val;
}

template <>
Int16::Operand(const std::string &value)
		: _string(value),
			_type(eOperandType::_int16)
{
	int32_t val = std::stoi(value);
	if (val > 0 && val > std::numeric_limits<int16_t>::max())
	{
		throw Operand::Overflow();
	}
	else if (val < 0 && val < std::numeric_limits<int16_t>::min())
	{
		throw Operand::Underflow();
	}
	this->_value = val;
}

template <>
Int32::Operand(const std::string &value)
		: _string(value),
			_type(eOperandType::_int32),
			_value(std::stoi(value)) {}

#endif
