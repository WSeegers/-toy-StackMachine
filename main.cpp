#include <regex>
#include <string>
#include <iostream>

#include "./Core/include/Core.hpp"

#include <fstream>
#include <iostream>

Lexer lex;

int main(int ac, char *av[])
{
	std::ifstream fis;

	switch (ac)
	{
	case 1:
		Parser().parse();
		break;
	case 2:
		fis.open(av[1]);
		// fis.open("./samples/02_push_all_types.avm"); //test
		if (!fis.is_open())
		{
			std::cerr << "Unable to open " << av[1] << std::endl;
			return 1;
		}
		Parser(&fis, &std::cout).parse();
		break;
	default:
		std::cerr << "Usage avm [ filename.avm ]" << av[1] << std::endl;
		return 1;
	}
}
