set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/PongFrame.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Game.h"

)
set(SUB_DIRECTORIES "States"
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
