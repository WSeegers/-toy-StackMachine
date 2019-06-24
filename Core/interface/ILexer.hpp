#ifndef ILEXER_HPP
#define ILEXER_HPP

#include "../include/Token.hpp"

#include <string>

class ILexer
{
public:
	virtual ~ILexer() {}

	virtual void tokenize(std::string input) = 0;
	virtual Token nextToken() = 0;
	virtual bool empty() = 0;
};

#endif
