#include "./test.hpp"
#include "../include/Core.hpp"

#include <sstream>

TEST_CASE("[PARSER-BASIC]")
{
	std::stringstream input;
	std::stringstream out;
	Parser parser(&input, &out);

	parser.setThrowErrors(true);

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

	input << "push float(16)" << std::endl;
	input << "assert float(16)" << std::endl;
	input << "pop" << std::endl;
	input << "push float(16.16)" << std::endl;
	input << "assert float(16.16)" << std::endl;
	input << "pop" << std::endl;
	input << "push float(-16)" << std::endl;
	input << "assert float(-16)" << std::endl;
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

TEST_CASE("[PARSER-ADDITION]")
{
	SECTION("Typing")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(0)" << std::endl;
		input << "push float(0)" << std::endl;
		input << "push int32(0)" << std::endl;
		input << "push int16(0)" << std::endl;
		input << "push int8(0)" << std::endl;

		input << "assert int8(0)" << std::endl;
		input << "add" << std::endl;
		input << "assert int16(0)" << std::endl;
		input << "add" << std::endl;
		input << "assert int32(0)" << std::endl;
		input << "add" << std::endl;
		input << "assert float(0)" << std::endl;
		input << "add" << std::endl;
		input << "assert double(0)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}

	SECTION("Functionality")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(1)" << std::endl;
		input << "push float(1)" << std::endl;
		input << "push int32(1)" << std::endl;
		input << "push int16(1)" << std::endl;
		input << "push int8(1)" << std::endl;

		input << "assert int8(1)" << std::endl;
		input << "add" << std::endl;
		input << "assert int16(2)" << std::endl;
		input << "add" << std::endl;
		input << "assert int32(3)" << std::endl;
		input << "add" << std::endl;
		input << "assert float(4)" << std::endl;
		input << "add" << std::endl;
		input << "assert double(5)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}
}

TEST_CASE("[PARSER-SUBTRACTION]")
{
	SECTION("Typing")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(0)" << std::endl;
		input << "push float(0)" << std::endl;
		input << "push int32(0)" << std::endl;
		input << "push int16(0)" << std::endl;
		input << "push int8(0)" << std::endl;

		input << "assert int8(0)" << std::endl;
		input << "sub" << std::endl;
		input << "assert int16(0)" << std::endl;
		input << "sub" << std::endl;
		input << "assert int32(0)" << std::endl;
		input << "sub" << std::endl;
		input << "assert float(0)" << std::endl;
		input << "sub" << std::endl;
		input << "assert double(0)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}

	SECTION("Functionality")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(1)" << std::endl;
		input << "push float(1)" << std::endl;
		input << "push int32(1)" << std::endl;
		input << "push int16(1)" << std::endl;
		input << "push int8(1)" << std::endl;

		input << "assert int8(1)" << std::endl;
		input << "sub" << std::endl;
		input << "assert int16(0)" << std::endl;
		input << "sub" << std::endl;
		input << "assert int32(-1)" << std::endl;
		input << "sub" << std::endl;
		input << "assert float(-2)" << std::endl;
		input << "sub" << std::endl;
		input << "assert double(-3)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}
}

TEST_CASE("[PARSER-MULTIPLICATION]")
{
	SECTION("Typing")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(1)" << std::endl;
		input << "push float(1)" << std::endl;
		input << "push int32(1)" << std::endl;
		input << "push int16(1)" << std::endl;
		input << "push int8(1)" << std::endl;

		input << "assert int8(1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert int16(1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert int32(1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert float(1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert double(1)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}

	SECTION("Functionality")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(-1)" << std::endl;
		input << "push float(-1)" << std::endl;
		input << "push int32(-1)" << std::endl;
		input << "push int16(-1)" << std::endl;
		input << "push int8(-1)" << std::endl;

		input << "assert int8(-1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert int16(1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert int32(-1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert float(1)" << std::endl;
		input << "mul" << std::endl;
		input << "assert double(-1)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}
}

TEST_CASE("[PARSER-DIVISION]")
{
	SECTION("Typing")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(1)" << std::endl;
		input << "push float(1)" << std::endl;
		input << "push int32(1)" << std::endl;
		input << "push int16(1)" << std::endl;
		input << "push int8(1)" << std::endl;

		input << "assert int8(1)" << std::endl;
		input << "div" << std::endl;
		input << "assert int16(1)" << std::endl;
		input << "div" << std::endl;
		input << "assert int32(1)" << std::endl;
		input << "div" << std::endl;
		input << "assert float(1)" << std::endl;
		input << "div" << std::endl;
		input << "assert double(1)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}

	SECTION("Functionality")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(-1)" << std::endl;
		input << "push float(-1)" << std::endl;
		input << "push int32(-1)" << std::endl;
		input << "push int16(-1)" << std::endl;
		input << "push int8(-1)" << std::endl;

		input << "assert int8(-1)" << std::endl;
		input << "div" << std::endl;
		input << "assert int16(1)" << std::endl;
		input << "div" << std::endl;
		input << "assert int32(-1)" << std::endl;
		input << "div" << std::endl;
		input << "assert float(1)" << std::endl;
		input << "div" << std::endl;
		input << "assert double(-1)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}
}

TEST_CASE("[PARSER-MODULO]")
{
	SECTION("Typing + Functionality")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		input << "push double(4)" << std::endl;
		input << "push float(4)" << std::endl;
		input << "push int32(4)" << std::endl;
		input << "push int16(4)" << std::endl;
		input << "push int8(2)" << std::endl;

		input << "assert int8(2)" << std::endl;
		input << "mod" << std::endl;
		input << "assert int16(2)" << std::endl;
		input << "mod" << std::endl;
		input << "assert int32(2)" << std::endl;
		input << "mod" << std::endl;
		input << "assert float(2)" << std::endl;
		input << "mod" << std::endl;
		input << "assert double(2)" << std::endl;
		REQUIRE_NOTHROW(parser.parse());
	}
}

TEST_CASE("[PARSER-PRINT]")
{
	SECTION("Functionality")
	{
		std::stringstream input;
		std::stringstream out;
		Parser parser(&input, &out);

		parser.setThrowErrors(true);

		std::string test("The quick brown fox jumps over the lazy dog");
		for (char c : test)
		{
			input << "push int8(" << int(c) << ")" << std::endl;
			input << "print" << std::endl;
			input << "pop" << std::endl;
		}

		REQUIRE_NOTHROW(parser.parse());
		REQUIRE(out.str() == test);
	}
}
