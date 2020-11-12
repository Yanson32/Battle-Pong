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

add_subdirectory("extlibs")
add_subdirectory("BattlePong")

string(TOUPPER "${CMAKE_BUILD_TYPE}" BP_BUILD_TYPE_UPPER)
if("${BP_BUILD_TYPE_UPPER}" STREQUAL "DEBUG")
	add_definitions("-DDEBUG")
endif()

#Make the BUILD_TESTING variable show up in the cmake gui
option(BUILD_TESTING "Set to TRUE if you want to build unit tests" FALSE)

file(COPY "Resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

