set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/IntroState.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/StateBase.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/PlayState.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/DemoState.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/StateId.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/States.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/CreditsState.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/LicenseState.h"

)
set(SUB_DIRECTORIES "")

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "include/States" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
