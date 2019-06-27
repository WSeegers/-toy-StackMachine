#ifndef PARSER
#define PARSER

#include "./Stack.hpp"
#include "../Lexer/include/Lexer.hpp"
#include "../Logger/include/Logger.hpp"

#include <istream>
#include <ostream>
#include <exception>
#include <map>

class Parser;

typedef void (Parser::*InstructionFunc)(void);
typedef std::map<std::string, InstructionFunc> InstructionMap;
typedef std::map<std::string, eOperandType> TypeMap;

class Parser : private Stack
{
private:
	// Stack stack;

	Lexer _lexer;
	std::istream *_is;
	std::ostream *_os;
	bool _throwError = false;

	static const InstructionMap instructionMap;
	static const TypeMap typeMap;

	void parsePush();
	void parseAssert();
	void dump();
	void print();
	void exit();

	void getValue();
	std::string parseInt();
	std::string parseFloat();

public:
	Parser();
	Parser(std::istream *is, std::ostream *os);
	Parser(Parser &cpy);
	~Parser();

	Parser &operator=(const Parser &rhs);

	const std::istream *is();
	void setInStream(std::istream *is);

	const std::ostream *os();
	void setOutStream(std::ostream *os);

	void setThrowErrors(bool b);

	void parse();

	struct InvalidToken;
};

struct Parser::InvalidToken : public std::exception
{
	const char *what() const throw();
};

#endif
