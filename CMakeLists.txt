#for backwards compatibility
cmake_minimum_required(VERSION 3.5.1)

#This must be above the project command
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "The projects build for example Debug/Release")

#Give the project a name
project("BattlePong" VERSION "1.0.0.0")
string(TOUPPER ${PROJECT_NAME} BP_PROJECT_NAME_UPPER)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

#Build shared library by default
option(BUILD_SHARED_LIBS "True for shared libraries" TRUE)

#Create our target
add_executable("${PROJECT_NAME}" "Main.cpp")

add_subdirectory("include")
add_subdirectory("src")




string(TOUPPER "${CMAKE_BUILD_TYPE}" BP_BUILD_TYPE_UPPER)
if("${BP_BUILD_TYPE_UPPER}" STREQUAL "DEBUG")
	add_definitions("-DDEBUG")
endif()


#Define compiler features
target_compile_features("${PROJECT_NAME}" 
			PRIVATE 
			cxx_nullptr
			cxx_right_angle_brackets
			)


#Add includes to target
target_include_directories("${PROJECT_NAME}" PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include>
	)

find_package(GameUtilities REQUIRED)
# and for each of your dependent executable/library targets:
target_link_libraries("${PROJECT_NAME}" PRIVATE GameUtilities)


find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
target_include_directories("${PROJECT_NAME}" PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries("${PROJECT_NAME}" PUBLIC ${SFML_LIBRARIES})

find_package(TGUI REQUIRED)
target_include_directories("${PROJECT_NAME}" PUBLIC ${TGUI_INCLUDE_DIR})
target_link_libraries("${PROJECT_NAME}" PUBLIC ${TGUI_LIBRARY})

find_package(Boost 1.60.0 COMPONENTS thread date_time filesystem system program_options regex system log log_setup REQUIRED)
target_link_libraries("${PROJECT_NAME}" PUBLIC ${Boost_LIBRARIES})
target_include_directories("${PROJECT_NAME}" PUBLIC ${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE
	PONG_B2_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D/*.cpp"
)

target_sources("${PROJECT_NAME}" PRIVATE ${PONG_B2_SOURCES})

target_include_directories("${PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Box2D")

#Export targets to the build tree
export(TARGETS "${PROJECT_NAME}" FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-Exports.cmake")


#Make the BUILD_TESTING variable show up in the cmake gui
option(BUILD_TESTING "Set to TRUE if you want to build unit tests" FALSE)

file(COPY "Resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
