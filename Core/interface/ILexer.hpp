#ifndef ILEXER_HPP
#define ILEXER_HPP

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
