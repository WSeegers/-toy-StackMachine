#include "util.hpp"

TEST_CASE("[FLOAT-INST]")
{
	test_float_instantiation<Float>();
}

TEST_CASE("[FLOAT-OPERATOR]")
{
	safe_float_operator_tests<Float>();
}
