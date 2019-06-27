#ifndef FLOATOP_HPP
#define FLOATOP_HPP

#include "Operand.hpp"

template <>
Float::Operand(const std::string &value)
		: _string(value),
			_value(std::stod(value)),
			_type(eOperandType::_float) {}

template <>
Double::Operand(const std::string &value)
		: _string(value),
			_value(std::stof(value)),
			_type(eOperandType::_double) {}

#endif
