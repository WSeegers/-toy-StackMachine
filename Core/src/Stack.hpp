#ifndef STACK_HPP
#define STACK_HPP

#include "OperandFactory.hpp"

#include <deque>

class Stack
{
private:
	std::deque<const IOperand *> _memory;
	OperandFactory _factory;
	Stack(const Stack &cpy);
	Stack &operator=(const Stack &rhs);

public:
	Stack();
	~Stack();

	void push(eOperandType type, const std::string &value);
	void pop();
	void dump(std::ostream &stream);
	void assert(eOperandType type, const std::string &value);
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print(std::ostream &os);

	struct Empty;
	struct InferiorStackSize;
	struct AssertTypeFail;
	struct AssertValueFail;
	struct NotPrintAbleValue;
};

struct Stack::InferiorStackSize : public std::exception
{
	const char *what() const throw();
};

struct Stack::AssertTypeFail : public std::exception
{
	const char *what() const throw();
};

struct Stack::AssertValueFail : public std::exception
{
	const char *what() const throw();
};

struct Stack::NotPrintAbleValue : public std::exception
{
	const char *what() const throw();
};

struct Stack::Empty : public std::exception
{
	const char *what() const throw();
};

#endif
