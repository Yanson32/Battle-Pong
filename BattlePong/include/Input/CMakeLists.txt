set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Input.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/AI.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/PlayerInput.h"


)
set(SUB_DIRECTORIES ""
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "include/Input" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})

	#Install source files
	install(FILES ${FILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_PATH}")
endif()
