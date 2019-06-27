#ifndef LEXER_HPP
#define LEXER_HPP

#include <regex>
#include <queue>
#include <string>
#include <exception>

class Token;

class Lexer
{
private:
	static const std::regex regInstruction;
	static const std::regex regValue;
	static const std::regex regFloat;
	static const std::regex regInt;
	static const std::regex regComment;
	static const std::regex blankLine;

	std::queue<Token> c;

	void getInstruction(std::string &input);
	void getValue(std::string &input);
	void getFloat(std::string &input);
	void getInt(std::string &input);

	int _idx = 0;

public:
	Lexer();
	~Lexer();

	void tokenize(std::string input);
	Token nextToken();
	bool empty();

	class LexigraphicalError;
	class NoToken;
};

class Lexer::LexigraphicalError : std::exception
{
private:
	std::string _message;
	int _idx;

public:
	LexigraphicalError();
	LexigraphicalError(const std::string &msg, int idx);
	LexigraphicalError(const LexigraphicalError &cpy);

	LexigraphicalError &operator=(const LexigraphicalError &rhs);

	const char *what() const throw();

	const std::string &message();
	int index();
};

class Lexer::NoToken : std::exception
{
	const char *what() const throw();
};
#endif
