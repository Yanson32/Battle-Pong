set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Settings.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/SFMLFunctions.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/TGUIFunctions.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Arguments.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/TS_TcpSocket.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/TS_TcpListener.cpp"
)
set(SUB_DIRECTORIES "Events"
					"Objects"
					"Input"
					"Box2D"
					"Gui"
                    "Resources"
                    "Network"
                    "Engin"
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "src" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
