#include "./test.hpp"
#include "../include/Core.hpp"

#include <sstream>

TEST_CASE("[PARSER-BASIC]")
{
	Lexer lex;
	std::stringstream input;
	std::stringstream out;
	Parser parser(&lex, &input, &out);

	input << "push int32(32)" << std::endl;
	input << "assert int32(32)" << std::endl;
	input << "pop" << std::endl;
	input << "push int32(-32)" << std::endl;
	input << "assert int32(-32)" << std::endl;
	input << "pop" << std::endl;

	input << "push int16(16)" << std::endl;
	input << "assert int16(16)" << std::endl;
	input << "pop" << std::endl;
	input << "push int16(-16)" << std::endl;
	input << "assert int16(-16)" << std::endl;
	input << "pop" << std::endl;

	input << "push int8(8)" << std::endl;
	input << "assert int8(8)" << std::endl;
	input << "pop" << std::endl;
	input << "push int8(-8)" << std::endl;
	input << "assert int8(-8)" << std::endl;
	input << "pop" << std::endl;

	input << "push float()" << std::endl;
	input << "assert float(16)" << std::endl;
	input << "pop" << std::endl;
	input << "push float(-16)" << std::endl;
	input << "assert float(-16)" << std::endl;
	input << "pop" << std::endl;

	input << "push double(16)" << std::endl;
	input << "assert double(16)" << std::endl;
	input << "pop" << std::endl;
	input << "push double(-16)" << std::endl;
	input << "assert double(-16)" << std::endl;
	input << "pop" << std::endl;

	REQUIRE_NOTHROW(parser.parse());
}