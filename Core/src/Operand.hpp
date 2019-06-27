#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"

#include <string>
#include <sstream>
#include <iomanip>
#include <exception>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <type_traits>

// Remove
#include <iostream>

template <typename T>
class Operand;

typedef Operand<int8_t> Int8;
typedef Operand<int16_t> Int16;
typedef Operand<int32_t> Int32;
typedef Operand<float> Float;
typedef Operand<double> Double;

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
	Operand() : Operand("0") {}
	Operand(const Operand<T> &cpy)
			: _string(cpy._string),
				_value(cpy._value),
				_type(cpy._type) {}

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
	void setValue(T value)
	{
		// This will preserve the highest possible accuracy
		std::stringstream coversion;
		coversion << std::setprecision(std::numeric_limits<T>::digits)
							<< value;
		this->_string = coversion.str();
		this->_value = value;
	}

	int getPrecision(void) const { return this->_type; }
	eOperandType getType(void) const { return this->_type; }
	virtual const std::string &toString(void) const { return this->_string; }

	virtual const IOperand *operator+(IOperand const &rhs) const
	{
		if (this->getPrecision() < rhs.getPrecision())
			return (rhs + *this);

		Operand<T> *ret = new Operand<T>(rhs.toString());

		T f1 = this->_value;
		T f2 = ret->_value;
		T max = std::numeric_limits<T>::max();
		T min = std::numeric_limits<T>::min();

		if (std::is_integral<T>::value)
		{
			if ((f2 > 0) && (f1 > max - f2))
			{
				delete ret;
				throw Operand::Overflow();
			}

			if ((f2 < 0) && (f1 < min - f2))
			{
				delete ret;
				throw Operand::Underflow();
			}
		}

		ret->setValue(this->_value + ret->_value);
		return ret;
	}

	virtual const IOperand *operator-(IOperand const &rhs) const
	{
		if (this->getPrecision() < rhs.getPrecision())
		{
			switch (rhs.getType())
			{
			case _double:
				return Operand<double>(this->_string) - rhs;
			case _float:
				return Operand<float>(this->_string) - rhs;
			case _int32:
				return Operand<int32_t>(this->_string) - rhs;
			case _int16:
				return Operand<int16_t>(this->_string) - rhs;
			case _int8:
				return Operand<int8_t>(this->_string) - rhs;
			}
		}

		Operand<T> *ret = new Operand<T>(rhs.toString());

		T f1 = this->_value;
		T f2 = ret->_value;
		T max = std::numeric_limits<T>::max();
		T min = std::numeric_limits<T>::min();

		if (std::is_integral<T>::value)
		{
			if ((f2 < 0) && (f1 > max + f2))
			{
				delete ret;
				throw Operand::Overflow();
			}

			if ((f2 > 0) && (f1 < min + f2))
			{
				delete ret;
				throw Operand::Underflow();
			}
		}

		ret->setValue(this->_value - ret->_value);
		return ret;
	}

	virtual const IOperand *operator*(IOperand const &rhs) const
	{
		if (this->getPrecision() < rhs.getPrecision())
			return (rhs * (*this));

		Operand<T> *ret = new Operand<T>(rhs.toString());

		T f1 = this->_value;
		T f2 = ret->_value;
		T max = std::numeric_limits<T>::max();
		T min = std::numeric_limits<T>::min();

		if (f1 == 1)
		{
		}
		else if (f2 == 1)
			ret->setValue(this->_value);
		else if ((f1 == 0) || (f2 == 0))
			ret->setValue(0);
		else if (std::is_integral<T>::value &&
						 (((f1 == -1) && (f2 == min)) || ((f2 == -1) && (f1 == min))))
		{
			delete ret;
			throw Operand::Overflow();
		}
		else if (std::is_integral<T>::value &&
						 ((f1 > 0) == (f2 > 0) && (std::abs(f1) > std::abs(max / f2))))
		{
			delete ret;
			throw Operand::Overflow();
		}
		else if (std::is_integral<T>::value &&
						 ((f2 > 0 && f1 > max / f2) || (f2 < 0 && f1 < max / f2)))
		{
			delete ret;
			throw Operand::Underflow();
		}
		else
			ret->setValue(this->_value * ret->_value);

		return ret;
	}

	virtual const IOperand *operator/(IOperand const &rhs) const
	{
		if (this->getPrecision() < rhs.getPrecision())
		{
			switch (rhs.getType())
			{
			case _double:
				return Operand<double>(this->_string) / rhs;
			case _float:
				return Operand<float>(this->_string) / rhs;
			case _int32:
				return Operand<int32_t>(this->_string) / rhs;
			case _int16:
				return Operand<int16_t>(this->_string) / rhs;
			case _int8:
				return Operand<int8_t>(this->_string) / rhs;
			}
		}

		Operand<T> *ret = new Operand<T>(rhs.toString());

		if (ret->_value == 0)
		{
			delete ret;
			throw Operand::DivZero();
		}

		T f1 = this->_value;
		T f2 = ret->_value;
		T min = std::numeric_limits<T>::min();

		if (std::is_integral<T>::value &&
				(((f1 == -1) && (f2 == min)) || ((f2 == -1) && (f1 == min))))
		{
			delete ret;
			throw Operand::Overflow();
		}

		ret->setValue(this->_value / ret->_value);
		return ret;
	}

	virtual const IOperand *operator%(IOperand const &rhs) const
	{
		if (this->getPrecision() < rhs.getPrecision())
		{
			switch (rhs.getType())
			{
			case _double:
				return Operand<double>(this->_string) % rhs;
			case _float:
				return Operand<float>(this->_string) % rhs;
			case _int32:
				return Operand<int32_t>(this->_string) % rhs;
			case _int16:
				return Operand<int16_t>(this->_string) % rhs;
			case _int8:
				return Operand<int8_t>(this->_string) % rhs;
			}
		}

		Operand<T> *ret = new Operand<T>(rhs.toString());

		if (ret->_value == 0)
		{
			delete ret;
			throw Operand::DivZero();
		}

		ret->setValue(std::remainder(this->_value, ret->_value));
		return ret;
	}

	virtual bool operator==(IOperand const &rhs) const
	{
		if (this->getPrecision() < rhs.getPrecision())
			return rhs == *this;

		return this->_value == Operand<T>(rhs.toString())._value;
	}

	static T getMax()
	{
		return std::numeric_limits<T>::max();
	}
	static T getMin() { return std::numeric_limits<T>::min(); }

	struct Overflow;
	struct Underflow;
	struct DivZero;
};

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

template <typename T>
struct Operand<T>::DivZero : public std::exception
{
	const char *what() const throw() { return "Divided by zero"; };
};

#include "Float.hpp"
#include "Int.hpp"

#endif
