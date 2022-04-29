set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/CustomPanel.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/GuiManager.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/ScorePanel.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/PaddleHud.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/PlayPanel.cpp"
)

set(RELATIVE_PATH "src")
set(SUB_DIRECTORIES "InfoPanel"
)

foreach(VAR ${SUB_DIRECTORIES})
	add_subdirectory(${VAR})
endforeach()

if(FILES)
	target_sources("${PROJECT_NAME}" PRIVATE ${FILES})
	install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
