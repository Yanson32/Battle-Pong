#for backwards compatibility
cmake_minimum_required(VERSION 3.5.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")
include ("defaults")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")

#make sure we are using a single configuration generator
if(CMAKE_BUILD_TYPE)
    #set CMAKE_BUILD_TYPE as a dropdown list in cmake gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "RelWithDebInfo" "MinRizeRel")
else()
    #set default value for CMAKE_BUILD_TYPE in multi-configuration generators.
    set(CMAKE_BUILD_TYPE CACHE STRING "Build configuration" "Release")
endif()

#Give the project a name
project("BattlePong" VERSION "1.0.0.0")

string(TOUPPER ${PROJECT_NAME} BP_PROJECT_NAME_UPPER)

#Build shared library by default
option(BUILD_SHARED_LIBS "True for shared libraries" TRUE)

set(${PROJECT_NAME}_VALID_BUILD_TYPES "Release" "Debug" "MinSizeRel" "RelWithDebInfo")

#set default build type
if(NOT CMAKE_CONFIGUREATION_TYPES)
	if(CMAKE_BUILD_TYPE STREQUAL "")
		set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Select build type [${${PROJECT_NAME}_VALID_BUILD_TYPES}]" FORCE)
	endif()
endif()

#set dropdown list in cmake gui
if(NOT CMAKE_CONFIGUREATION_TYPES)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${${PROJECT_NAME}_VALID_BUILD_TYPES})
endif()

add_subdirectory("extlibs")
add_subdirectory("BattlePong")

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

string(TOUPPER "${CMAKE_BUILD_TYPE}" BP_BUILD_TYPE_UPPER)
if("${BP_BUILD_TYPE_UPPER}" STREQUAL "DEBUG")
	add_definitions("-DDEBUG")
endif()

configure_file("${${PROJECT_NAME}_SOURCE_DIR}/cmake/config.h.in" "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}/config.h")

#Make the BUILD_TESTING variable show up in the cmake gui
option(BUILD_TESTING "Set to TRUE if you want to build unit tests" FALSE)

if(NOT CMAKE_CONFIGURATION_TYPES)
	file(COPY "Resources/" DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/Resources/")
endif()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/" DESTINATION "Resources")
