#for backwards compatibility 
cmake_minimum_required(VERSION 3.5.1)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")
include ("Debug")
include ("Help")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")

#Give the project a name
project("BattlePong" VERSION "0.0.0.1")
help_text()
debug_init()

string(TOUPPER ${PROJECT_NAME} BP_PROJECT_NAME_UPPER)

#Build shared library by default
#option(BUILD_SHARED_LIBS "True for shared libraries" TRUE)

set(${PROJECT_NAME}_VALID_BUILD_TYPES "Release" "Debug" "MinSizeRel" "RelWithDebInfo")

#Throw error on invalid build type
if(NOT CMAKE_CONFIGUREATION_TYPES)
    #Throw error on invalid build type
    string(FIND "${${PROJECT_NAME}_VALID_BUILD_TYPES}" "${CMAKE_BUILD_TYPE}" BUILD_TYPE_RESULT) 
    if(${BUILD_TYPE_RESULT} EQUAL -1 OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
        message(FATAL_ERROR "Invalid build type [${CMAKE_BUILD_TYPE}] valid types are ${${PROJECT_NAME}_VALID_BUILD_TYPES}]")
    endif()
    
    #set dropdown list in cmake gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${${PROJECT_NAME}_VALID_BUILD_TYPES})
endif()

#include operating system specific code
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/${CMAKE_SYSTEM_NAME}.cmake")
	include("${CMAKE_SYSTEM_NAME}")
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

configure_file("${${PROJECT_NAME}_SOURCE_DIR}/cmake/config.h.in" "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}/config.h")

#Make the BUILD_TESTING variable show up in the cmake gui
option(BUILD_TESTING "Set to TRUE if you want to build unit tests" FALSE)


file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/"  DESTINATION "${BP_GAME_CONFIG_DIR}")
