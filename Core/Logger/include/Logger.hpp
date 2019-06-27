#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

namespace Logger
{
void LexicalError(const std::string &msg, int line, int index);
void RuntimeError(const std::string &msg, int line);
}; // namespace Logger

#endif
