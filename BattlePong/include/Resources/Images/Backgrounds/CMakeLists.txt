set(FILES   "${CMAKE_CURRENT_SOURCE_DIR}/Star.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Nebula.h"

)

set(SUB_DIRECTORIES "")

set(RELATIVE_PATH "include/Resources/Images/Backgrounds")

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
