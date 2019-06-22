#include "util.hpp"

TEST_CASE("[DOUBLE-INST]")
{
	test_float_instantiation<Double>();
}

TEST_CASE("[DOUBLE-OPERATOR]")
{
	safe_float_operator_tests<Double>();
}
