#include "Stack.hpp"

#include <stdexcept>
#include <ostream>

Stack::Stack() {}
Stack::~Stack()
{
	while (!this->_memory.empty())
	{
		delete this->_memory.back();
		this->_memory.pop_back();
	}
}

void Stack::push(eOperandType type, const std::string &value)
{
	this->_memory.push_back(this->_factory.createOperand(type, value));
}

void Stack::pop()
{
	delete this->_memory.back();
	this->_memory.pop_back();
};

void Stack::dump(std::ostream &stream)
{
	for (const IOperand *op : this->_memory)
		stream << op->toString() << std::endl;
};

void Stack::assert(eOperandType type, const std::string &value)
{
	if (this->_memory.empty())
		throw Stack::Empty();

	const IOperand *op = this->_memory.back();
	if (op->getType() != type)
		throw Stack::AssertTypeFail();

	const IOperand *tmp = this->_factory.createOperand(type, value);
	bool valid = *tmp == *op;
	delete tmp;
	if (!valid)
		throw Stack::AssertValueFail();
}

void Stack::add()
{
	const IOperand *f1 = this->_memory.back();
	const IOperand *f2 = this->_memory.back();

	const IOperand *next = *f1 + *f2;

	this->_memory.pop_back();
	this->_memory.pop_back();
	this->_memory.push_back(next);
	delete f1;
	delete f2;
}

void Stack::sub()
{
	const IOperand *f1 = this->_memory.back();
	const IOperand *f2 = this->_memory.back();

	const IOperand *next = *f1 - *f2;

	this->_memory.pop_back();
	this->_memory.pop_back();
	this->_memory.push_back(next);
	delete f1;
	delete f2;
}

void Stack::mul()
{
	const IOperand *f1 = this->_memory.back();
	const IOperand *f2 = this->_memory.back();

	const IOperand *next = *f1 * *f2;

	this->_memory.pop_back();
	this->_memory.pop_back();
	this->_memory.push_back(next);
	delete f1;
	delete f2;
}

void Stack::div()
{
	const IOperand *f1 = this->_memory.back();
	const IOperand *f2 = this->_memory.back();

	const IOperand *next = *f1 / *f2;

	this->_memory.pop_back();
	this->_memory.pop_back();
	this->_memory.push_back(next);
	delete f1;
	delete f2;
}

void Stack::mod()
{
	const IOperand *f1 = this->_memory.back();
	const IOperand *f2 = this->_memory.back();

	const IOperand *next = *f1 % *f2;

	this->_memory.pop_back();
	this->_memory.pop_back();
	this->_memory.push_back(next);
	delete f1;
	delete f2;
}

void Stack::print(std::ostream &os)
{
	try
	{
		OperandFactory::printOperand(*this->_memory.back(), os);
	}
	catch (const std::exception &e)
	{
		throw Stack::NotPrintAbleValue();
	}
}

const char *Stack::InferiorStackSize::what() const throw()
{
	return "Stack size of atleast 2 is required";
};

const char *Stack::AssertTypeFail::what() const throw()
{
	return "Type is incorrect";
};

const char *Stack::AssertValueFail::what() const throw()
{
	return "Value is incorrect";
};

const char *Stack::NotPrintAbleValue ::what() const throw()
{
	return "Type of Int8 is required";
};

const char *Stack::Empty::what() const throw()
{
	return "Stack is empty";
};
