set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/SoundId.h"
            	"${CMAKE_CURRENT_SOURCE_DIR}/MusicId.h"
	    	"${CMAKE_CURRENT_SOURCE_DIR}/TextureId.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/Resource Holder.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/ResourceManager.h"

)
set(SUB_DIRECTORIES "Images"
                    "Fonts"
                    "Music"
                    "Sounds"
                    "TGUI"
)

set(RELATIVE_PATH "Resources")

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
