#ifndef FLOAT_HPP
#define FLOAT_HPP

#include "Operand.hpp"

template <>
Float::Operand(const std::string &value)
		: _string(value),
			_type(eOperandType::_float),
			_value(std::stod(value)) {}

template <>
Double::Operand(const std::string &value)
		: _string(value),
			_type(eOperandType::_double),
			_value(std::stof(value)) {}

#endif
