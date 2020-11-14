set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/IntroState.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/StateBase.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/PlayState.cpp"
#			"${CMAKE_CURRENT_SOURCE_DIR}/ControlState.cpp"
#			"${CMAKE_CURRENT_SOURCE_DIR}/PaddleState.cpp"
#			"${CMAKE_CURRENT_SOURCE_DIR}/MusicState.cpp"
#			"${CMAKE_CURRENT_SOURCE_DIR}/MultiPlayerControlsState.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/SingleplayerState.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/DemoState.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/HostState.cpp"
#			"${CMAKE_CURRENT_SOURCE_DIR}/ConnectState.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/HostPlayState.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ClientPlayState.cpp"
)
set(SUB_DIRECTORIES "")

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
