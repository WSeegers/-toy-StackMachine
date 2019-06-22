add_library(
	Core
	# src/OpInt16.cpp
	# src/OpInt32.cpp
	# src/Double.cpp
	# src/Int32.cpp
	src/OperandFactory.cpp
	)

target_include_directories(Core PUBLIC "./include")

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
