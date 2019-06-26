#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>
#include <ostream>

class ILogger
{
public:
    virtual void LexicalError(std::ostream &os, std::string &msg, int line) = 0;
    virtual void LexicalError(std::ostream &os, std::string &msg, int line) = 0;
};

#endif