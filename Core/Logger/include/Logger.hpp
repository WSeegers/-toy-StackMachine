#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../../interface/ILogger.hpp"

class Logger : ILogger
{
    virtual void LexicalError(std::string &msg, int line);
    virtual void RuntimeError(std::string &msg, int line);
};

#endif