#ifndef PARSER
#define PARSER

#include "./Stack.hpp"
#include "../interface/ILexer.hpp"

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

	ILexer *_lexer;
	std::istream *_is;
	std::ostream *_os;

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
	Parser(ILexer *lexer);
	Parser(ILexer *lexer, std::istream *is, std::ostream *os);
	Parser(Parser &cpy);
	~Parser();

	const ILexer *lexer();
	void setLexer(ILexer *lexer);

	const std::istream *is();
	void setLexer(std::istream *is);

	const std::ostream *os();
	void setLexer(std::ostream *os);

	Parser &operator=(const Parser &rhs);

	void parse();

	struct NullLexer;
	struct InvalidToken;
};

struct Parser::NullLexer : public std::exception
{
	const char *what() const throw();
};

struct Parser::InvalidToken : public std::exception
{
	const char *what() const throw();
};

#endif
