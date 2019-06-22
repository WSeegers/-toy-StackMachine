#include "util.hpp"

TEST_CASE("Int32", "[INT32]")
{
	test_int_instantiation<Int32>();
	test_int_overflow<Int32>();
	overflow_tests<Int32>();

	// addition_tests<Int32>();
}
