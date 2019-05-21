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

#Create our target
add_executable("${PROJECT_NAME}" "Main.cpp")

set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 14)

add_subdirectory("extlibs")
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
			cxx_decltype_auto
			)


#Add includes to target
target_include_directories("${PROJECT_NAME}" PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include>
	)

find_package(GameUtilities COMPONENTS Core Event Engin REQUIRED)
target_link_libraries("${PROJECT_NAME}" PRIVATE GU::Core GU::Event GU::Engin)

find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
target_include_directories("${PROJECT_NAME}" PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries("${PROJECT_NAME}" PUBLIC ${SFML_LIBRARIES})

find_package(TGUI REQUIRED)
target_include_directories("${PROJECT_NAME}" PUBLIC ${TGUI_INCLUDE_DIR})
target_link_libraries("${PROJECT_NAME}" PUBLIC ${TGUI_LIBRARY})

find_package(Boost 1.60.0 COMPONENTS thread date_time filesystem system program_options regex system log log_setup REQUIRED)
target_link_libraries("${PROJECT_NAME}" PUBLIC ${Boost_LIBRARIES})
target_include_directories("${PROJECT_NAME}" PUBLIC ${Boost_INCLUDE_DIRS})

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/Box2D")
target_link_libraries("${PROJECT_NAME}" PUBLIC Box2D)

#Export targets to the build tree
export(TARGETS "${PROJECT_NAME}" FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-Exports.cmake")


#Make the BUILD_TESTING variable show up in the cmake gui
option(BUILD_TESTING "Set to TRUE if you want to build unit tests" FALSE)

file(COPY "Resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
