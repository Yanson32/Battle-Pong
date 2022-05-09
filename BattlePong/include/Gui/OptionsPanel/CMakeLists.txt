set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/OptionsPanel.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/DevPanel.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/GeneralPanel.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/MultiplayerPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/HostPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ConnectPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ControlPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/SoundPanel.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/VideoPanel.h"
)

set(RELATIVE_PATH "include")
set(SUB_DIRECTORIES ""
)

foreach(VAR ${SUB_DIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	target_sources("${PROJECT_NAME}" PRIVATE ${FILES})
	install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
