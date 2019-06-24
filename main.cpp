#include <regex>
#include <string>
#include <iostream>

#include "./Core/include/Core.hpp"

Lexer lex;

void test(std::string s)
{
}

int main()
{
	Lexer lex;
	Parser parser(&lex);

	parser.parse();
}
