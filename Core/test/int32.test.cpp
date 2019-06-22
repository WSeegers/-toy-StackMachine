#include "util.hpp"

TEST_CASE("[INT32-INST]")
{
	test_int_instantiation<Int32>();
}

TEST_CASE("[INT32-OVERFLOW]")
{
	overflow_tests<Int32>();
}

TEST_CASE("[INT32-OPERATOR]")
{
	safe_operator_tests<Int32>();
}
