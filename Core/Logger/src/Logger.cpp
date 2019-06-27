#include "../include/Logger.hpp"

#include <iostream>

void Logger::LexicalError(const std::string &msg, int line, int index)
{
	std::cerr << "Lexical Error -> "
						<< line << ":" << index << " : " << msg << std::endl;
}

void Logger::RuntimeError(const std::string &msg, int line)
{
	std::cerr << "Runtime Error -> Line "
						<< line << " : " << msg << std::endl;
}
