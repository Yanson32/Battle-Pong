set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Paddle.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Settings.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/DebugDraw.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Ball.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Box2DFunctions.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Wall.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ObjectBase.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/AI.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/PlayerInput.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/MusicListener.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ResourceManager.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/SoundListener.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ContactListener.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/BallCollisionListener.cpp"

)
set(SUB_DIRECTORIES "States"
					"Events"
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
