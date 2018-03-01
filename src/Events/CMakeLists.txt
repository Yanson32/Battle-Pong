set(FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/EventBase.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/PlayMusic.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/EventManager.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/PlaySound.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/BallCollision.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/MusicVolumeChanged.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Id.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/SoundVolumeChanged.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/GoalCollision.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/LeftPaddleGoal.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/RightPaddleGoal.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/PaddleCollision.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/ChangeState.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/Pop.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/PushState.cpp"

)
set(SUB_DIRECTORIES "Listener")

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
