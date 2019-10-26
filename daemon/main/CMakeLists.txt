set(MODULE_NAME ${PROJECT_NAME})
project(${MODULE_NAME})
message("")
message("MODULE_NAME --> " ${MODULE_NAME})

find_package (Threads)
SET(CMAKE_CXX_FLAGS -pthread)

file(GLOB SOURCES "*.cxx" "*.cpp" "*/*.cpp" "*.h" "*.hpp")
file(GLOB HEADER "*.h" "*.hpp" "*/*.h" "*/*.hpp")
message("ProjectSources ( " ${MODULE_NAME} " ) = " ${SOURCES})
message("ProjectHeader ( " ${MODULE_NAME} " ) = " ${HEADER})

add_executable(${MODULE_NAME} ${SOURCES})

install(TARGETS ${MODULE_NAME} DESTINATION "/usr/bin/" )
