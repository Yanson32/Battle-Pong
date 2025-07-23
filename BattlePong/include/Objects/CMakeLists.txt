set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/ObjectBase.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Wall.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Ball.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Paddle.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/Goal.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/PaddleStop.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ObjectId.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Objects.h"

)
set(SUB_DIRECTORIES ""
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "include/Objects" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
