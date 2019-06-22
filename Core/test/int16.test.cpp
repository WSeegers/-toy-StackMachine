#include "util.hpp"

TEST_CASE("Int16", "[INT16]")
{
	test_int_instantiation<Int16>();
	test_int_overflow<Int16>();
	overflow_tests<Int16>();

	// addition_tests<Int16>();
}
