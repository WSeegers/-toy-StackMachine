#include "../include/Lexer.hpp"
#include "../../include/Token.hpp"

#include <iostream>

const std::regex Lexer::regInstruction(
		"^ *(push"
		"|pop"
		"|dump"
		"|assert"
		"|add"
		"|sub"
		"|mul"
		"|div"
		"|mod"
		"|print"
		"|exit)");

const std::regex Lexer::regValue(
		"^ *(int8"
		"|int16"
		"|int32"
		"|float"
		"|double)");

const std::regex Lexer::regFloat("^\\( *([-]?\\d+\\.\\d+) *\\)");

const std::regex Lexer::regInt("^\\( *([-]?\\d+) *\\)");

const std::regex Lexer::regComment(";.*");

const std::regex Lexer::blankLine("\\s*");

Lexer::Lexer() {}
Lexer::~Lexer() {}

void Lexer::tokenize(std::string input)
{
	this->_idx = 0;
	if (std::regex_match(input, blankLine) || std::regex_match(input, regComment))
		return;
	this->getInstruction(input);
}

void Lexer::getInstruction(std::string &input)
{
	std::smatch m;
	if (std::regex_search(input, m, regInstruction))
	{
		Token inst(Token::eTokenType::instruction, m[1].str());
		this->_idx += m[0].length();
		this->c.push(inst);
		input = m.suffix().str();
		if (inst.value() == "push" || inst.value() == "assert")
			this->getValue(input);
	}
	else
		throw LexigraphicalError("Instruction expected", this->_idx);
}

void Lexer::getValue(std::string &input)
{

	std::smatch m;
	if (std::regex_search(input, m, regValue))
	{
		Token val(Token::eTokenType::valueType, m[1].str());
		this->_idx += m[0].length();
		this->c.push(val);
		input = m.suffix().str();

		if (val.value().find("int") == -1)
			this->getFloat(input);
		else
			this->getInt(input);
	}
	else
		throw LexigraphicalError("Value type expected", this->_idx);
}

void Lexer::getFloat(std::string &input)
{
	std::smatch m;
	if (std::regex_search(input, m, regFloat) || std::regex_search(input, m, regInt))
	{
		Token flt(Token::eTokenType::floatingPoint, m[1].str());
		this->_idx += m[0].length();
		this->c.push(flt);
		input = m.suffix().str();
	}
	else
		throw LexigraphicalError("Floating point value expected", this->_idx);
}

void Lexer::getInt(std::string &input)
{
	std::smatch m;
	if (std::regex_search(input, m, regInt))
	{
		Token _int(Token::eTokenType::integer, m[1].str());
		this->_idx += m[0].length();
		this->c.push(_int);
		input = m.suffix().str();
	}
	else
		throw LexigraphicalError("Integer value expected", this->_idx);
}

Token Lexer::nextToken()
{
	if (this->empty())
		throw NoToken();
	Token ret = this->c.front();
	this->c.pop();
	return ret;
}

bool Lexer::empty() { return this->c.empty(); }

Lexer::LexigraphicalError::LexigraphicalError() : _idx(0) {}
Lexer::LexigraphicalError::LexigraphicalError(const LexigraphicalError &cpy)
		: _message(cpy._message),
			_idx(cpy._idx) {}

Lexer::LexigraphicalError &
Lexer::LexigraphicalError::operator=(const LexigraphicalError &rhs)
{
	if (this != &rhs)
	{
		this->_message = rhs._message;
		this->_idx = rhs._idx;
	}
	return *this;
}

Lexer::LexigraphicalError::LexigraphicalError(const std::string &msg, int line)
		: _message(msg),
			_idx(line) {}

const char *Lexer::LexigraphicalError::what() const throw()
{
	return _message.c_str();
}

const std::string &Lexer::LexigraphicalError::message() { return this->_message; }
int Lexer::LexigraphicalError::index() { return this->_idx; }

const char *Lexer::NoToken::what() const throw()
{
	return "Lexer contains no tokens";
}
