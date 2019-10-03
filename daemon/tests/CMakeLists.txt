set(MODULE_NAME ${PROJECT_NAME}Tests)

cmake_minimum_required(VERSION 3.10)
project(${MODULE_NAME})

set(CMAKE_CXX_FLAGS  -pthread)

# include_directories(lib/googletest/googletest/include)

file(GLOB SOURCES "main.cpp" "src/*/*.cpp" "../src/*/*.hpp"  "../src/*/*.cpp") 

message(${SOURCES})
add_executable(${MODULE_NAME} ${SOURCES})

target_include_directories(${MODULE_NAME} PRIVATE  ../src/Logging/ ../src/ArgumentParser/ ../src/ExampleModule/)

target_link_libraries(${MODULE_NAME}  gtest)

cmake_minimum_required(VERSION 3.2)