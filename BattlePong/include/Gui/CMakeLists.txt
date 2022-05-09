set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/CustomPanel.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/GuiManager.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/ButtonId.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ScorePanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/PaddleHud.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/PlayPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/IntroPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/SliderId.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ComboId.h"
)

set(RELATIVE_PATH "include")
set(SUB_DIRECTORIES "OptionsPanel"
)

foreach(VAR ${SUB_DIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	target_sources("${PROJECT_NAME}" PRIVATE ${FILES})
	install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
