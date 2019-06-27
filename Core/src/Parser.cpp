#include "./Parser.hpp"
#include "../include/Token.hpp"

#include <iostream>
#include <functional>
#include <stdexcept>

const InstructionMap Parser::instructionMap = {
		{"push", &Parser::parsePush},
		{"pop", &Parser::pop},
		{"dump", &Parser::dump},
		{"assert", &Parser::parseAssert},
		{"add", &Parser::add},
		{"sub", &Parser::sub},
		{"mul", &Parser::mul},
		{"div", &Parser::div},
		{"mod", &Parser::mod},
		{"print", &Parser::print},
		{"exit", &Parser::exit}};

const TypeMap Parser::typeMap = {
		{"int8", _int8},
		{"int16", _int16},
		{"int32", _int32},
		{"float", _float},
		{"double", _double}};

Parser::Parser() : Parser(&std::cin, &std::cout) {}
Parser::Parser(Parser &cpy) : Parser(cpy._is, cpy._os) {}
Parser::Parser(std::istream *is, std::ostream *os)
		: _is(is),
			_os(os) {}
Parser::~Parser() {}

Parser &Parser::operator=(const Parser &rhs)
{
	if (this != &rhs)
	{
		this->_is = rhs._is;
		this->_os = rhs._os;
	}
	return *this;
}

const std::istream *Parser::is() { return this->_is; }
void Parser::setInStream(std::istream *is)
{
	this->_is = (is) ? is : &std::cin;
}

const std::ostream *Parser::os() { return this->_os; }
void Parser::setOutStream(std::ostream *os)
{
	this->_os = (os) ? os : &std::cout;
}

void Parser::parse()
{
	int lineCount = 0;
	bool lexError = false;

	std::istream &is(*(this->_is));
	std::string line;
	while (!is.eof())
	{
		std::getline(is, line);
		if (this->_is == &std::cin && line[0] == ';' && line[1] == ';')
			break;
		try
		{
			this->_lexer.tokenize(line);
		}
		catch (Lexer::LexigraphicalError e)
		{
			if (this->_throwError)
				throw std::runtime_error(e.what());
			Logger::LexicalError(e.message(), lineCount, e.index());
			lexError = true;
		}
		lineCount++;
	}

	if (lexError)
		return;

	Token token;
	while (!this->_lexer.empty())
	{
		token = this->_lexer.nextToken();
		if (token.tokenType() != Token::eTokenType::instruction)
			throw InvalidToken();
		InstructionFunc inst = Parser::instructionMap.at(token.value());
		try
		{
			(this->*inst)();
		}
		catch (std::exception &e)
		{
			Logger::RuntimeError(e.what(), 0);
		}
	}
}

void Parser::parsePush()
{
	eOperandType type;
	std::string value;

	Token token = this->_lexer.nextToken();
	if (token.tokenType() != Token::eTokenType::valueType)
		throw InvalidToken();

	type = Parser::typeMap.at(token.value());

	token = this->_lexer.nextToken();
	if (!(token.tokenType() == Token::eTokenType::integer ||
				token.tokenType() == Token::eTokenType::floatingPoint))
		throw InvalidToken();

	value = token.value();

	this->Stack::push(type, value);
}

void Parser::parseAssert()
{
	eOperandType type;
	std::string value;

	Token token = this->_lexer.nextToken();
	if (token.tokenType() != Token::eTokenType::valueType)
		throw InvalidToken();

	type = Parser::typeMap.at(token.value());

	token = this->_lexer.nextToken();
	if (!(token.tokenType() == Token::eTokenType::integer ||
				token.tokenType() == Token::eTokenType::floatingPoint))
		throw InvalidToken();

	value = token.value();

	this->Stack::_assert(type, value);
}

void Parser::dump() { this->Stack::dump(*(this->_os)); }
void Parser::print() { this->Stack::print(*(this->_os)); }
void Parser::exit() { throw "Not Implimented"; }

const char *Parser::InvalidToken::what() const throw()
{
	return "Token is invalid";
}

void Parser::setThrowErrors(bool b) { this->_throwError = b; }
