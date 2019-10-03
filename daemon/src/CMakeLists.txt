set(MODULE_NAME ${PROJECT_NAME})

cmake_minimum_required(VERSION 3.10)
project(${MODULE_NAME})

find_package (Threads)
SET(CMAKE_CXX_FLAGS -pthread)

file(GLOB SOURCES "*.cxx" "*.cpp" "*/*.cpp" "*.h" "*.hpp")
file(GLOB HEADER "*.h" "*.hpp" "*/*.h" "*/*.hpp")

add_executable(${MODULE_NAME} ${SOURCES})

install(TARGETS ${MODULE_NAME} DESTINATION "/usr/bin/" )
