add_library(
	Lexer
	src/Lexer.cpp
	src/Token.cpp
	)

target_include_directories(Lexer PUBLIC "../interface")
target_include_directories(Lexer PUBLIC "../include")
