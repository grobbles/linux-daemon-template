cmake_minimum_required (VERSION 3.10)
project (daemon)

# Version Definition  #####################################################
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)


# Modules  #################################################################
add_subdirectory(daemon)


# Package Generator  #######################################################
SET(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_DESCRIPTION "A daemon example")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Uwe Roder")
set(CPACK_PACKAGE_VENDOR "UWE_RODER")
set(CPACK_PACKAGE_CONTACT "uweroder@gmail.com")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr/bin")
include (CPack)