#ifndef LEXER_HPP
#define LEXER_HPP

#include "../../interface/ILexer.hpp"

#include <regex>
#include <queue>
#include <string>

class Token;
class ILexer;

class Lexer : public ILexer
{
private:
	static const std::regex regInstruction;
	static const std::regex regValue;
	static const std::regex regFloat;
	static const std::regex regInt;
	static const std::regex regComment;

	std::queue<Token> c;

	bool getInstruction(std::string &input);
	void getValue(std::string &input);
	void getFloat(std::string &input);
	void getInt(std::string &input);

public:
	Lexer();
	~Lexer();

	virtual void tokenize(std::string input);
	virtual Token nextToken();
	virtual bool empty();
};

#endif
