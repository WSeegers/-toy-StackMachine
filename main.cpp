#include <regex>
#include <string>
#include <iostream>

#include "./Lexer/src/Lexer.hpp"

Lexer lex;

void test(std::string s)
{
	std::cout << std::endl
						<< s << std::endl;
	lex.tokenize(s);
}

int main()
{
	test("push int32(42)");
	test("push int32(-33)");
	test("add");
	test("mul");
	test("assert double( -42.42)");

	std::cout << std::endl;

	while (!lex.empty())
	{
		Token t(lex.nextToken());
		std::cout << t.tokenType() << ": " << t.value() << std::endl;
	}
}
