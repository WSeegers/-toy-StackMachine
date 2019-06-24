#ifndef LEXER_HPP
#define LEXER_HPP

/*
S := INSTR [SEP INSTR]* #

INSTR :=
	push VALUE
	| pop
	| dump
	| assert VALUE
	| add
	| sub
	| mul
	| div
	| mod
	| print
	| exit

VALUE :=
	int8(N)
	| int16(N)
	| int32(N)
	| float(Z)
	| double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'+
*/
#include "Token.hpp"
#include "ILexer.hpp"

#include <regex>
#include <queue>
#include <string>

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
