set(MODULE_NAME ${PROJECT_NAME}Tests)

cmake_minimum_required(VERSION 3.10)
project(${MODULE_NAME})

add_subdirectory(lib/googletest)

# SET(CMAKE_CXX_FLAGS --Wwrite-strings)

include_directories(${SOURCE_DIR}) 
include_directories(lib/googletest/googletest/include)

file(GLOB SOURCES "*.cpp" "src/*.cpp" "src/*/*.cpp")

add_executable(${MODULE_NAME} ${SOURCES})
target_link_libraries(${MODULE_NAME} ExampleModule  gtest)

install(TARGETS ${MODULE_NAME} DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})