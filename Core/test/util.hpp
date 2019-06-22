#ifndef TESTULTI_HPP
#define TESTULTI_HPP

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Operand.hpp"

#include <sstream>
#include <limits>
#include <type_traits>
#include <cstdlib>
#include <random>
#include <iomanip>

template <typename T>
void test_int_instantiation()
{
	auto test = [](auto x) {
		T testOp(std::to_string(x));
		auto actual = testOp.getValue();

		REQUIRE(actual == x);
	};

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(T::getMin(), T::getMin());

	for (int i = 0; i < 1000; i++)
		test(distribution(generator));
}

template <typename T>
void test_float_instantiation()
{
	auto test = [](auto x) {
		std::stringstream stringVal;
		stringVal << std::setprecision(std::numeric_limits<float>::digits)
							<< x;
		T testOp(stringVal.str());
		auto actual = testOp.getValue();
		auto diff = std::abs(actual - x);
		double epsilon = std::numeric_limits<float>::epsilon();

		REQUIRE(diff < epsilon);
	};

	test(0.3);
	test(-0.3);
	test(1.6);
	test(-1.9);
	test(1.33451234);
	test(5.434);
	test(-1.45);
	test(2.432);
	test(3.3333);
	test(-3.3333);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(-1.0, 1.0);
	for (int i = 0; i < 1000; i++)
		test(distribution(generator));
}

template <typename T>
void test_int_overflow()
{
	int64_t max = static_cast<int64_t>(T::getMax()) + 1;
	int64_t min = static_cast<int64_t>(T::getMin()) - 1;

	REQUIRE_THROWS(T(std::to_string(max)));
	REQUIRE_THROWS(T(std::to_string(min)));
}

template <typename T>
void overflow_tests()
{
	auto test = [](auto x) {
		T testOp(std::to_string(x));
		auto actual = testOp.getValue();

		REQUIRE(actual == x);
	};

	int64_t max = static_cast<int64_t>(T::getMax());
	int64_t min = static_cast<int64_t>(T::getMin());

	test(max);
	test(min);

	REQUIRE_THROWS(T(std::to_string(max + 1)));
	REQUIRE_THROWS(T(std::to_string(min - 1)));

	const T one("1");
	const T negOne("-1");
	const T maxOp(std::to_string(max));
	const T minOp(std::to_string(min));

	REQUIRE_THROWS(maxOp + one);
	REQUIRE_THROWS(minOp + negOne);
}

#endif
