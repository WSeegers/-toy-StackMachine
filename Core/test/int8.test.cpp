#include "util.hpp"

TEST_CASE("Int8", "[INT8]")
{
	test_int_instantiation<Int8>();
	test_int_overflow<Int8>();
	overflow_tests<Int8>();
	// addition_tests<Int8>();
}
