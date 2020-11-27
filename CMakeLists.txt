#for backwards compatibility
cmake_minimum_required(VERSION 3.5.1)

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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

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

#Set default compiler flags
if(NOT DEFINED ${PROJECT_NAME}_IS_FIRST_RUN)
	set(${PROJECT_NAME}_IS_FIRST_RUN False CACHE INTERNAL "Used to determine if current run is first run")

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -Wall -pedantic" CACHE STRING "Compiler variables for debug mode" FORCE)
	endif()
endif()

add_subdirectory("extlibs")
add_subdirectory("BattlePong")

string(TOUPPER "${CMAKE_BUILD_TYPE}" BP_BUILD_TYPE_UPPER)
if("${BP_BUILD_TYPE_UPPER}" STREQUAL "DEBUG")
	add_definitions("-DDEBUG")
endif()

#Make the BUILD_TESTING variable show up in the cmake gui
option(BUILD_TESTING "Set to TRUE if you want to build unit tests" FALSE)

if(NOT CMAKE_CONFIGURATION_TYPES)
	file(COPY "Resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
endif()
