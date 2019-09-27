get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" MODULE_NAME ${MODULE_NAME})
message("MODULE_NAME = " ${MODULE_NAME})

cmake_minimum_required(VERSION 3.10)
project(${MODULE_NAME} C CXX)

file(GLOB SOURCES "*.cxx" "*.cpp" "*.h" "*.hpp" "../*/*.cpp")
file(GLOB HEADER_FILES "*.h" "*.hpp" "../*/*.hpp")
add_library(${MODULE_NAME} SHARED STATIC ${SOURCES})

install(TARGETS ${MODULE_NAME} DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES ${HEADER_FILES} DESTINATION ${DIVISIBLE_INSTALL_INC_DIR})
