#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "OperandFactory.hpp"

bool basicTypeTest(eOperandType type)
{
	OperandFactory factory;

	const IOperand *op;
	op = factory.createOperand(type, "6");
	bool ret = op->getType() == type;
	delete op;
	return ret;
}

TEST_CASE("Type Test On Creation", "[TYPE]")
{
	OperandFactory factory;

	const IOperand *i8 = factory.createOperand(_int8, "1");
	const IOperand *i16 = factory.createOperand(_int16, "1");
	const IOperand *i32 = factory.createOperand(_int32, "1");
	const IOperand *ft = factory.createOperand(_float, "1");
	const IOperand *dbl = factory.createOperand(_double, "1");

	const IOperand *ops[] = {i8, i16, i32, ft, dbl};

	SECTION("At instantiation")
	{
		REQUIRE(basicTypeTest(_int8));
		REQUIRE(basicTypeTest(_int16));
		REQUIRE(basicTypeTest(_int32));
		REQUIRE(basicTypeTest(_float));
		REQUIRE(basicTypeTest(_double));
	}

	SECTION("Type after Addition")
	{
		for (const IOperand *op1 : ops)
		{
			for (const IOperand *op2 : ops)
			{
				const IOperand *test = *op1 + *op2;

				const eOperandType type1 = op1->getType();
				const eOperandType type2 = op2->getType();

				const eOperandType expected = std::max(type1, type2);
				const eOperandType actual = test->getType();

				REQUIRE(expected == actual);
			}
		}
	}
}
