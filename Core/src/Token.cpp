#include "../include/Token.hpp"

Token::Token() {}

Token::Token(eTokenType tokenType, const std::string &value, int idx)
		: _tokenType(tokenType),
			_value(value),
			_idx(idx) {}

Token::Token(const Token &cpy)
		: Token(cpy._tokenType, cpy._value, cpy._idx) {}

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
