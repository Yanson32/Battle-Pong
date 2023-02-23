set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/CustomPanel.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/GuiManager.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/GuiId.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ScorePanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/PaddleHud.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/PlayPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/IntroPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/CreditsPanel.h"
)

set(RELATIVE_PATH "include/Gui")
set(SUB_DIRECTORIES "OptionsPanel"
)

foreach(VAR ${SUB_DIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	target_sources("${PROJECT_NAME}" PRIVATE ${FILES})
	install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
