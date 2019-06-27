#ifndef INTOP_HPP
#define INTOP_HPP

#include "Operand.hpp"

#include <limits>
#include <string>

template <>
Int8::Operand(const std::string &value)
		: _string(value),
			_type(eOperandType::_int8)
{
	// std::cout << value << std::endl;
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
void Int8::setValue(int8_t value)
{
	// This will preserve the highest possible accuracy
	std::stringstream coversion;
	coversion << std::setprecision(std::numeric_limits<int8_t>::digits)
						<< static_cast<int32_t>(value);
	this->_string = coversion.str();
	this->_value = value;
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
			_value(0),
			_type(eOperandType::_int32)
{
	try
	{
		this->_value = std::stoi(value);
	}
	catch (const std::exception &e)
	{
		throw Operand::Overflow();
	}
}

#endif
