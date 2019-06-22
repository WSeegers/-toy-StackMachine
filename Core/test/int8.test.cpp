#include "util.hpp"

TEST_CASE("[INT8-INST]")
{
	test_int_instantiation<Int8>();
}

TEST_CASE("[INT8-OVERFLOW]")
{
	overflow_tests<Int8>();
}

TEST_CASE("[INT8-OPERATOR]")
{
	safe_operator_tests<Int8>();
}
