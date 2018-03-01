set(FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/EventBase.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/PlayMusic.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/EventManager.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/PlaySound.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/BallCollision.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/MusicVolumeChanged.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Id.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/SoundVolumeChanged.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/GoalCollision.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/LeftPaddleGoal.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/RightPaddleGoal.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/PaddleCollision.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/ChangeState.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Events.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Pop.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/PushState.h"

)
set(SUB_DIRECTORIES "Listeners")

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
