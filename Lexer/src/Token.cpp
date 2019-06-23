#include "./Token.hpp"

Token::Token() {}

Token::Token(eTokenType tokenType, const std::string &value)
		: _tokenType(tokenType), _value(value) {}

Token::Token(const Token &cpy)
		: Token(cpy._tokenType, cpy._value) {}

Token::~Token() {}

const Token &Token::operator=(const Token &rhs)
{
	if (this != &rhs)
	{
		this->_tokenType = rhs._tokenType;
		this->_value = rhs._value;
	}
	return *this;
}

Token::eTokenType Token::tokenType() { return this->_tokenType; }
const std::string &Token::value() { return this->_value; }
