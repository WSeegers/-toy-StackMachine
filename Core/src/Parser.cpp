#include "./Parser.hpp"

#include <iostream>
#include <functional>

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

Parser::Parser() : Parser(nullptr) {}
Parser::Parser(ILexer *lexer) : Parser(lexer, &std::cin, &std::cout) {}
Parser::Parser(Parser &cpy) : Parser(cpy._lexer, cpy._is, cpy._os) {}
Parser::Parser(ILexer *lexer, std::istream *is, std::ostream *os)
		: _lexer(lexer),
			_is(is),
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

const ILexer *Parser::lexer() { return this->_lexer; }
void Parser::setLexer(ILexer *lexer) { this->_lexer = lexer; }

const std::istream *Parser::is() { return this->_is; }
void Parser::setLexer(std::istream *is)
{
	this->_is = (is) ? is : &std::cin;
}

const std::ostream *Parser::os() { return this->_os; }
void Parser::setLexer(std::ostream *os)
{
	this->_os = (os) ? os : &std::cout;
}

void Parser::parse()
{
	if (!this->_lexer)
		throw NullLexer();

	std::istream &is(*(this->_is));
	std::string line;
	while (!is.eof())
	{
		std::getline(is, line);
		// Handle end of program
		if (this->_is == &std::cin && line[0] == ';' && line[1] == ';')
			break;
		this->_lexer->tokenize(line);
	}

	Token token;
	while (!this->_lexer->empty())
	{
		token = this->_lexer->nextToken();
		if (token.tokenType() != Token::eTokenType::instruction)
			throw InvalidToken();
		InstructionFunc inst = Parser::instructionMap.at(token.value());
		(this->*inst)();
	}
}

void Parser::parsePush()
{
	eOperandType type;
	std::string value;

	Token token = this->_lexer->nextToken();
	if (token.tokenType() != Token::eTokenType::valueType)
		throw InvalidToken();

	type = Parser::typeMap.at(token.value());

	token = this->_lexer->nextToken();
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

	Token token = this->_lexer->nextToken();
	if (token.tokenType() != Token::eTokenType::valueType)
		throw InvalidToken();

	type = Parser::typeMap.at(token.value());

	token = this->_lexer->nextToken();
	if (!(token.tokenType() == Token::eTokenType::integer ||
				token.tokenType() == Token::eTokenType::floatingPoint))
		throw InvalidToken();

	value = token.value();

	this->Stack::assert(type, value);
}

void Parser::dump() { this->Stack::dump(*(this->_os)); }
void Parser::print() { this->Stack::print(*(this->_os)); }
void Parser::exit() { throw "Not Implimented"; }

const char *Parser::NullLexer::what() const throw()
{
	return "Lexer is null";
}

const char *Parser::InvalidToken::what() const throw()
{
	return "Token is invalid";
}
