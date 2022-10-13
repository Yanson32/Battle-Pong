set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/DebugDraw.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Box2DFunctions.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ContactListener.cpp"

)
set(SUB_DIRECTORIES ""
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "src/Box2D" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})

	#Install source files
	install(FILES ${FILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_PATH}")
endif()
