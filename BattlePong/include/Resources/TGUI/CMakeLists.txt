set(FILES 	""
)

set(SUB_DIRECTORIES "Theme"
)

set(RELATIVE_PATH "include/Resources/TGUI")

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
