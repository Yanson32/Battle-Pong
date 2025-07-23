set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/DebugDraw.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Box2DFunctions.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/ContactListener.h"

)
set(SUB_DIRECTORIES ""
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "include/Box2D" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
