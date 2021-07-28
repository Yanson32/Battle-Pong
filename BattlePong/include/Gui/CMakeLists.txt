set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/ControlPanel.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/CustomPanel.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/GuiManager.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/ButtonId.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/SoundPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ScorePanel.h"
			#"${CMAKE_CURRENT_SOURCE_DIR}/TimerPanel.h"
)

set(RELATIVE_PATH "include")
set(SUB_DIRECTORIES "IntroState"
)

foreach(VAR ${SUB_DIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	target_sources("${PROJECT_NAME}" PRIVATE ${FILES})
	install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
