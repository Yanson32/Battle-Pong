set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/NetMan.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Server.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Client.h"

)
set(SUB_DIRECTORIES ""
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "include" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
