#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token
{
public:
	enum eTokenType
	{
		instruction,
		seperator,
		valueType,
		integer,
		floatingPoint,
		paren,
	};

private:
	eTokenType _tokenType;
	std::string _value;

public:
	Token();
	Token(eTokenType tokenType, const std::string &value);
	Token(const Token &cpy);
	~Token();

	const Token &operator=(const Token &rhs);

	eTokenType tokenType();
	const std::string &value();
};

#endif
