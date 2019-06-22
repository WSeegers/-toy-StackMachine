#include "IOperand.hpp"
#include "Operand.hpp"
// #include "Int32.hpp"
// #include "Double.hpp"

#include <stdexcept>
#include <iostream>
#include <string>
#include <limits>

int main()
{
	// Int32 i("1");
	// Double d("1.5");

	Double d("1.4");
	Operand<int32_t> i("1");
	Operand<int32_t> ol(std::to_string(std::numeric_limits<int32_t>::max()));

	const IOperand *opI = i + i;
	const IOperand *opD = d + d;
	const IOperand *opM = i + d;

	std::cout << opI->toString() << " : " << opI->getType() << std::endl;
	std::cout << opD->toString() << " : " << opD->getType() << std::endl;
	std::cout << opM->toString() << " : " << opM->getType() << std::endl;

	delete opI;
	delete opD;
	delete opM;

	try
	{
		opI = ol + i;
		delete opI;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}
