add_subdirectory(Lexer)
add_subdirectory(Logger)

add_library(
	Core
	src/OperandFactory.cpp
	src/Stack.cpp
	src/Parser.cpp
	src/Token.cpp
	)

target_link_libraries(Core PUBLIC Lexer Logger)
# target_include_directories(Core PRIVATE ./Lexer/include ./Logger/include)

# Tests

add_executable(TypeTest test/type.test.cpp)
target_include_directories(TypeTest PUBLIC "../Catch")
target_link_libraries(TypeTest PRIVATE Core)
add_test(TypeTest TypeTest)

add_executable(Int8Test test/int8.test.cpp)
target_include_directories(Int8Test PUBLIC "../Catch")
target_link_libraries(Int8Test PRIVATE Core)
add_test(Int8Test Int8Test)

add_executable(Int16Test test/int16.test.cpp)
target_include_directories(Int16Test PUBLIC "../Catch")
target_link_libraries(Int16Test PRIVATE Core)
add_test(Int16Test Int16Test)

add_executable(Int32Test test/int32.test.cpp)
target_include_directories(Int32Test PUBLIC "../Catch")
target_link_libraries(Int32Test PRIVATE Core)
add_test(Int32Test Int32Test)

add_executable(FloatTest test/float.test.cpp)
target_include_directories(FloatTest PUBLIC "../Catch")
target_link_libraries(FloatTest PRIVATE Core)
add_test(FloatTest FloatTest)

add_executable(DoubleTest test/double.test.cpp)
target_include_directories(DoubleTest PUBLIC "../Catch")
target_link_libraries(DoubleTest PRIVATE Core)
add_test(DoubleTest DoubleTest)

add_executable(ParserTest test/parser.test.cpp)
target_include_directories(ParserTest PUBLIC "../Catch")
target_link_libraries(ParserTest PRIVATE Core)
add_test(ParserTest ParserTest)
