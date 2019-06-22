#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"

#include <string>
#include <sstream>
#include <iomanip>
#include <exception>
#include <limits>

// Remove
#include <iostream>

template <typename T>
class Operand : public IOperand
{
private:
	void setString();

protected:
	std::string _string;
	T _value;
	eOperandType _type;

public:
	Operand(const std::string &string);
	Operand() : _string("0"), _value(0) {}
	Operand(const Operand<T> &cpy)
			: _string(cpy._string),
				_value(cpy._value),
				_type(cpy.type) {}

	Operand<T> &operator=(Operand<T> &rhs)
	{
		if (this != &rhs)
		{
			this->_string = rhs._string;
			this->_type = rhs._type;
			this->_value = rhs._value;
		}
	};

	virtual ~Operand(void) {}

	T getValue() const { return this->_value; }

	int getPrecision(void) const { return this->_type; }
	eOperandType getType(void) const { return this->_type; }
	virtual const std::string &toString(void) const { return this->_string; }

	virtual const IOperand *operator+(IOperand const &rhs) const
	{
		if (this->getPrecision() < rhs.getPrecision())
			return (rhs + *this);

		Operand<T> *ret = new Operand<T>(rhs.toString());

		if (this->_value > 0 && ret->_value > 0)
		{
			T max = std::numeric_limits<T>::max();
			if (max - this->_value < ret->_value)
			{
				delete ret;
				throw Operand::Overflow();
			}
		}
		else if (this->_value < 0 && ret->_value < 0)
		{
			T min = std::numeric_limits<T>::min();
			if (min - this->_value > ret->_value)
			{
				delete ret;
				throw Operand::Underflow();
			}
		}

		ret->_value += this->_value;
		std::stringstream coversion;
		coversion << std::setprecision(std::numeric_limits<T>::digits)
							<< ret->_value;
		ret->_string = coversion.str();

		return ret;
	}

	virtual const IOperand *operator-(IOperand const &rhs) const
	{
		return this;
	}
	virtual const IOperand *operator*(IOperand const &rhs) const { return this; }
	virtual const IOperand *operator/(IOperand const &rhs) const { return this; }
	virtual const IOperand *operator%(IOperand const &rhs) const { return this; }

	static T getMax() { return std::numeric_limits<T>::max(); }
	static T getMin() { return std::numeric_limits<T>::min(); }

	struct Overflow;
	struct Underflow;
};

typedef Operand<int8_t> Int8;
typedef Operand<int16_t> Int16;
typedef Operand<int32_t> Int32;
typedef Operand<float> Float;
typedef Operand<double> Double;

template <typename T>
struct Operand<T>::Overflow : public std::exception
{
	const char *what() const throw() { return "Overflow"; };
};

template <typename T>
struct Operand<T>::Underflow : public std::exception
{
	const char *what() const throw() { return "Underflow"; };
};

#include "Float.hpp"
#include "Int.hpp"

#endif
