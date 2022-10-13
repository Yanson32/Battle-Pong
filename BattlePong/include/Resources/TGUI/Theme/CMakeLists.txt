set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/BabyBluePng.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/BlackPng.h"
	    	"${CMAKE_CURRENT_SOURCE_DIR}/BabyBlueTxt.h"
		    "${CMAKE_CURRENT_SOURCE_DIR}/BlackTxt.h"
		    "${CMAKE_CURRENT_SOURCE_DIR}/TransparentGreyTxt.h"

)
set(SUB_DIRECTORIES ""
)

set(RELATIVE_PATH "include/Resources/TGUI/Theme")

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})

	#Install source files
	install(FILES ${FILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_PATH}")
endif()
