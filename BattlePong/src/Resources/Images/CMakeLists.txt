set(FILES ""
)
set(SUB_DIRECTORIES "Black"
                    "BabyBlue"
                    "Default"
                    "Backgrounds"
                    "Icons"
                    "Credits"
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "src/Resources/Images" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
