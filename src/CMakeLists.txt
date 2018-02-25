set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Settings.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ResourceManager.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Debugging.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/PaddleHud.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Logging.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp"
)
set(SUB_DIRECTORIES "States"
					"Events"
					"Objects"
					"Input"
					"Box2D"
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "(/|\\|\)(include|src|test)(/|\\|\).*" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})

	#Install source files
	install(FILES ${FILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_PATH}")
endif()
