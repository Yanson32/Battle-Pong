#for backwards compatibility
cmake_minimum_required(VERSION 3.5.1)

#Give the project a name
project("Pong" VERSION "1.0.0.0")
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

#Build shared library by default
option(BUILD_SHARED_LIBS "True for shared libraries" TRUE)

#Create our target
add_executable("${PROJECT_NAME}" "Main.cpp")

add_subdirectory("include")
add_subdirectory("src")

#Change the library output path
set_target_properties( "${PROJECT_NAME}"
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY lib
    LIBRARY_OUTPUT_DIRECTORY lib
    RUNTIME_OUTPUT_DIRECTORY bin
)

#Define compiler features
target_compile_features("${PROJECT_NAME}" 
			PRIVATE 
			cxx_nullptr
			cxx_right_angle_brackets
			)

#Set the c++ standard
set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 11)

#Add includes to target
target_include_directories("${PROJECT_NAME}" PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include>
	)

find_package(GameUtilities REQUIRED)
# and for each of your dependent executable/library targets:
target_link_libraries("${PROJECT_NAME}" PUBLIC "GameUtilities")


find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
target_include_directories("${PROJECT_NAME}" PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries("${PROJECT_NAME}" PUBLIC ${SFML_LIBRARIES})

find_package(Box2D REQUIRED)
target_include_directories("${PROJECT_NAME}" PUBLIC ${BOX2D_INCLUDE_DIRS})
target_link_libraries("${PROJECT_NAME}" PUBLIC ${BOX2D_LIBRARIES})

find_package(TGUI 0.7 REQUIRED)
target_include_directories("${PROJECT_NAME}" PUBLIC ${TGUI_INCLUDE_DIR})
target_link_libraries("${PROJECT_NAME}" PUBLIC ${TGUI_LIBRARY})

find_package(Boost 1.60.0 COMPONENTS thread date_time filesystem regex system log log_setup REQUIRED)
target_link_libraries("${PROJECT_NAME}" PUBLIC ${Boost_LIBRARIES})
target_include_directories("${PROJECT_NAME}" PUBLIC ${Boost_INCLUDE_DIRS})

#Install Source Files
install(TARGETS "${PROJECT_NAME}" DESTINATION lib EXPORT "${PROJECT_NAME}-Exports")
install(EXPORT "${PROJECT_NAME}-Exports" DESTINATION "lib/cmake/${PROJECT_NAME}")


#Export targets to the build tree
export(TARGETS "${PROJECT_NAME}" FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-Exports.cmake")


#Make the BUILD_TESTING variable show up in the cmake gui
option(BUILD_TESTING "Set to TRUE if you want to build unit tests" FALSE)


