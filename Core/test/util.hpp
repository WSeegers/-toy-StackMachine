#ifndef TESTULTI_HPP
#define TESTULTI_HPP

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/Operand.hpp"

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

	REQUIRE_THROWS(maxOp - negOne);
	REQUIRE_THROWS(minOp - one);

	REQUIRE_THROWS(minOp * negOne);
	REQUIRE_THROWS(minOp * minOp);
	REQUIRE_THROWS(maxOp * maxOp);
}

template <typename T>
void safe_operator_tests()
{
	T f1;
	T f2;
	T f3;
	const T *added;
	const T *subtracted;
	const T *multiplied1;
	const T *multiplied2;
	const T *divided;

	int v1;
	int v2;
	int m;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(T::getMin() / 10, T::getMax() / 10);
	std::uniform_int_distribution<int> multiplier(-9, 9);

	for (int i = 0; i < 10000; i++)
	{
		v1 = distribution(generator);
		v2 = distribution(generator);
		m = multiplier(generator);

		f1.setValue(v1);
		f2.setValue(v2);
		f3.setValue(m);

		added = dynamic_cast<const T *>(f1 + f2);
		subtracted = dynamic_cast<const T *>(f1 - f2);
		multiplied1 = dynamic_cast<const T *>(f1 * f3);
		multiplied2 = dynamic_cast<const T *>(f2 * f3);

		REQUIRE(added->getValue() == v1 + v2);
		REQUIRE(subtracted->getValue() == v1 - v2);
		REQUIRE(multiplied1->getValue() == v1 * m);
		REQUIRE(multiplied2->getValue() == v2 * m);

		delete added;
		delete subtracted;
		delete multiplied1;
		delete multiplied2;

		if (v2 != 0)
		{
			divided = dynamic_cast<const T *>(f1 / f2);
			REQUIRE(divided->getValue() == v1 / v2);
			delete divided;
		}
	}
}

template <typename T>
void safe_float_operator_tests()
{
	T f1;
	T f2;
	const T *added;
	const T *subtracted;
	const T *multiplied;
	const T *divided;

	int v1;
	int v2;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(-1.0, 1.0);

	float epsilon = std::numeric_limits<float>::epsilon();
	auto validate = [epsilon](auto f1, auto f2) {
		auto diff = std::abs(f1 - f2);
		REQUIRE(diff < epsilon);
	};

	for (int i = 0; i < 10000; i++)
	{

		v1 = distribution(generator);
		v2 = distribution(generator);

		f1.setValue(v1);
		f2.setValue(v2);

		added = dynamic_cast<const T *>(f1 + f2);
		subtracted = dynamic_cast<const T *>(f1 - f2);
		multiplied = dynamic_cast<const T *>(f1 * f2);

		validate(added->getValue(), v1 + v2);
		validate(subtracted->getValue(), v1 - v2);
		validate(multiplied->getValue(), v1 * v2);

		delete added;
		delete subtracted;
		delete multiplied;

		if (v2 != 0)
		{
			divided = dynamic_cast<const T *>(f1 / f2);
			validate(divided->getValue(), v1 / v2);
			delete divided;
		}
	}
}

#endif
