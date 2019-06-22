#include "util.hpp"

TEST_CASE("[INT16-INST]")
{
	test_int_instantiation<Int16>();
}

TEST_CASE("[INT16-OVERFLOW]")
{
	overflow_tests<Int16>();
}

TEST_CASE("[INT16-OPERATOR]")
{
	safe_operator_tests<Int16>();
}
