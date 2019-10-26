set(MODULE_NAME ${PROJECT_NAME}Tests)
project(${MODULE_NAME})
message("")
message("MODULE_NAME --> " ${MODULE_NAME})

set(CMAKE_CXX_FLAGS  -pthread)

file(GLOB SOURCES "gTestMain.cpp" "main/*/*.cpp" "../main/*/*.hpp"  "../main/*/*.cpp") 
message("ProjectSources ( " ${MODULE_NAME} " ) = " ${SOURCES})

add_executable(${MODULE_NAME} ${SOURCES})

target_include_directories(${MODULE_NAME} PRIVATE  ../main/Logging/ ../main/ArgumentParser/ ../main/ExampleModule/)

target_link_libraries(${MODULE_NAME}  gtest)