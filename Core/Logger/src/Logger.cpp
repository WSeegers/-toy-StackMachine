#include "../include/logger.hpp"

#include <iostream>

void LexicalError(std::string &msg, int line)
{
    std::cerr << "Lexical Error | Line " << line << ":" << msg << std::endl;
}

void RuntimeError(std::string &msg, int line)
{
    std::cerr << "Runtime Error | Line " << line << ":" << msg << std::endl;
}