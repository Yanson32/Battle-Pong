#Create our target
add_executable("${PROJECT_NAME}" "Main.cpp")

target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCE_BINARY_PATH="${${PROJECT_NAME}_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)

set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

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
target_link_libraries("${PROJECT_NAME}" PUBLIC tgui)

find_package(Boost COMPONENTS thread date_time filesystem system program_options regex system log log_setup REQUIRED)
target_link_libraries("${PROJECT_NAME}" PUBLIC ${Boost_LIBRARIES})
target_include_directories("${PROJECT_NAME}" PUBLIC ${Boost_INCLUDE_DIRS})

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/Box2D")
target_link_libraries("${PROJECT_NAME}" PUBLIC Box2D)

#Export targets to the build tree
export(TARGETS "${PROJECT_NAME}" FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}-Exports.cmake")

