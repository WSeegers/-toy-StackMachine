#include "Stack.hpp"

#include <stdexcept>

Stack::Stack() {}
Stack::~Stack()
{
	while (!this->_memory.empty())
	{
		delete this->_memory.top();
		this->_memory.pop();
	}
}

void Stack::push(eOperandType type, const std::string &value)
{
	this->_memory.push(this->_factory.createOperand(type, value));
}

void Stack::pop()
{
	delete this->_memory.top();
	this->_memory.pop();
};

std::string Stack::dump()
{
	throw std::runtime_error("Not Implimented");
	return std::string();
};

void Stack::assert(eOperandType type, const std::string &value)
{
	if (this->_memory.empty())
		throw Stack::Empty();

	const IOperand *op = this->_memory.top();
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
	const IOperand *f1 = this->_memory.top();
	this->_memory.pop();
	const IOperand *f2 = this->_memory.top();
	this->_memory.pop();

	this->_memory.push(*f1 + *f2);
	delete f1;
	delete f2;
}

void Stack::sub()
{
	const IOperand *f1 = this->_memory.top();
	this->_memory.pop();
	const IOperand *f2 = this->_memory.top();
	this->_memory.pop();

	this->_memory.push(*f1 - *f2);
	delete f1;
	delete f2;
}

void Stack::mul()
{
	const IOperand *f1 = this->_memory.top();
	this->_memory.pop();
	const IOperand *f2 = this->_memory.top();
	this->_memory.pop();

	this->_memory.push(*f1 * *f2);
	delete f1;
	delete f2;
}

void Stack::div()
{
	const IOperand *f1 = this->_memory.top();
	this->_memory.pop();
	const IOperand *f2 = this->_memory.top();
	this->_memory.pop();

	this->_memory.push(*f1 / *f2);
	delete f1;
	delete f2;
}

void Stack::mod()
{
	const IOperand *f1 = this->_memory.top();
	this->_memory.pop();
	const IOperand *f2 = this->_memory.top();
	this->_memory.pop();

	this->_memory.push(*f1 % *f2);
	delete f1;
	delete f2;
}

void Stack::print()
{
	if (this->_memory.top()->getType() != _int8)
		throw Stack::NotPrintAbleValue();
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
