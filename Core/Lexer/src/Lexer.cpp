#include "../include/Lexer.hpp"

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

const std::regex Lexer::regComment(";.*[\\n|\\n\\r]");

Lexer::Lexer() {}
Lexer::~Lexer() {}

void Lexer::tokenize(std::string input)
{
	this->getInstruction(input);
}

bool Lexer::getInstruction(std::string &input)
{
	std::smatch m;
	if (std::regex_search(input, m, regInstruction))
	{
		Token inst(Token::eTokenType::instruction, m[1].str());
		this->c.push(inst);
		input = m.suffix().str();
		if (inst.value() == "push" || inst.value() == "assert")
			this->getValue(input);
		return true;
	}
	else
		return false;
}

void Lexer::getValue(std::string &input)
{

	std::smatch m;
	if (std::regex_search(input, m, regValue))
	{
		Token val(Token::eTokenType::valueType, m[1].str());
		this->c.push(val);
		input = m.suffix().str();

		if (val.value().find("int") == -1)
			this->getFloat(input);
		else
			this->getInt(input);
	}
	else
	{
		// Handle bad value type
		std::cout << "Bad Value Type" << std::endl;
	}
}

void Lexer::getFloat(std::string &input)
{

	std::smatch m;
	if (std::regex_search(input, m, regFloat) || std::regex_search(input, m, regInt))
	{
		Token flt(Token::eTokenType::floatingPoint, m[1].str());
		this->c.push(flt);
		input = m.suffix().str();
	}
	else
	{
		// Handle bad Float
		std::cout << "Bad Float" << std::endl;
		throw "Bad Float";
	}
}

void Lexer::getInt(std::string &input)
{
	std::smatch m;
	if (std::regex_search(input, m, regInt))
	{
		Token _int(Token::eTokenType::integer, m[1].str());
		this->c.push(_int);
		input = m.suffix().str();
	}
	else
	{
		// Handle bad Int
		std::cout << "Bad Int" << std::endl;
	}
}

Token Lexer::nextToken()
{
	Token ret = this->c.front();
	this->c.pop();
	return ret;
}

bool Lexer::empty() { return this->c.empty(); }
