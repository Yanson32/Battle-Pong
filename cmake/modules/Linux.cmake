set(ICON_LOCAL_DIRECTORY "$ENV{HOME}/.local/share/icons")
set(ICON_GLOBAL_DIRECTORY "/usr/share/icons")
set(ICON_DIRECTORY "")

#Find the correct local icon directory
foreach(ICON_DIR ${ICON_LOCAL_DIRECTORY})
	if(EXISTS ${ICON_DIR})	
		set(ICON_DIRECTORY ${ICON_DIR})
	endif()
endforeach()

#Find the correct global icon directory
if(${PROJECT_NAME}_GLOBAL_INSTALL)
	foreach(ICON_DIR ${ICON_GLOBAL_DIRECTORY})	
		if(EXISTS "${ICON_DIR}")
			set(ICON_DIRECTORY ${ICON_DIR})
		endif()
	endforeach()
endif()


#Install application icon
if(EXISTS "${ICON_DIRECTORY}")
	install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/Resources/Icons/${PROJECT_NAME}.png" DESTINATION "${ICON_DIRECTORY}")
endif()


set(DESKTOP_LOCAL_DIRECTORY "$ENV{HOME}/.local/share/applications")
set(DESKTOP_GLOBAL_DIRECTORY "/usr/share/applications")
set(DESKTOP_DIRECTORY "")


#Find the local desktop directory
foreach(DESKTOP_DIR ${DESKTOP_LOCAL_DIRECTORY})
	if(EXISTS "${DESKTOP_DIR}")
		set(DESKTOP_DIRECTORY "${DESKTOP_DIR}")	
	else()
		message("Desktop directory does not exist ${DESKTOP_DIR}")
	endif()
endforeach()

#Find the correct global desktop directory
if(${PROJECT_NAME}_GLOBAL_INSTALL)
	foreach(DESKTOP_DIR ${DESKTOP_GLOBAL_DIRECTORY})	
		if(EXISTS "${DESKTOP_DIR}")
			set(DESKTOP_DIRECTORY ${DESKTOP_DIR})
		endif()
	endforeach()
endif()

#Create desktop file
if(EXISTS ${ICON_DIRECTORY})
	file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop"
	"[Desktop Entry]
	Name=${PROJECT_NAME}
	Exec=/usr/local/bin/${PROJECT_NAME}
	Terminal=false
	Icon=${ICON_DIRECTORY}/${PROJECT_NAME}.png
	Type=Application"
	)
endif()

#Install desktop file
if(EXISTS "${DESKTOP_DIRECTORY}") 
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop" DESTINATION "${DESKTOP_DIRECTORY}")
endif()

unset(DESKTOP_LOCAL_DIRECTORY)
unset(DESKTOP_GLOBAL_DIRECTORY)
unset(DESKTOP_DIRECTORY)
unset(ICON_LOCAL_DIRECTORY)
unset(ICON_GLOBAL_DIRECTORY)
unset(ICON_DIRECTORY)

set(CONFIG_DIR "$ENV{HOME}/.config/${PROJECT_NAME}")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/" DESTINATION "${CONFIG_DIR}")
target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCE_INSTALL_PATH="${CONFIG_DIR}")
unset(CONFIG_DIR)

