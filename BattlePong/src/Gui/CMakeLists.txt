set(FILES 	#"${CMAKE_CURRENT_SOURCE_DIR}/ScorePanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ControlPanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/CustomPanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/GuiManager.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/IntroGui.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/OptionsPanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/DevPanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/GeneralPanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/MultiplayerPanel.cpp"
			#"${CMAKE_CURRENT_SOURCE_DIR}/OptionsPanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/SoundPanel.cpp"
			#"${CMAKE_CURRENT_SOURCE_DIR}/IntroPanel.cpp"
			#"${CMAKE_CURRENT_SOURCE_DIR}/TimerPanel.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/HostPanel.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/ConnectPanel.cpp"
)

set(RELATIVE_PATH "src")
set(SUB_DIRECTORIES ""
)

foreach(VAR ${SUB_DIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	target_sources("${PROJECT_NAME}" PRIVATE ${FILES})
	install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
