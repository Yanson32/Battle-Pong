set(ICON_LOCAL_DIRECTORY "$ENV{HOME}/.local/share/icons")
set(ICON_GLOBAL_DIRECTORY "/usr/share/icons;/usr/share/app-install/desktop/")
set(ICON_DIRECTORY "")

#Find the correct local icon directory
foreach(ICON_DIR ${ICON_LOCAL_DIRECTORY})
	if(EXISTS ${ICON_DIR})	
		set(ICON_DIRECTORY ${ICON_DIR})
	endif()
endforeach()

#Create variable for global install
set(BP_GLOBAL_INSTALL TRUE CACHE BOOL "Set to true if doing a global install")
debug_report("Global Install = ${BP_GLOBAL_INSTALL}")

#Find the correct global icon directory
if(BP_GLOBAL_INSTALL)
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
else()
    debug_report("Linux.cmake: Icon directory does not exist. Icon Directory = ${ICON_DIRECTORY}")
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


#Create the games config directory
set(BP_GAME_CONFIG_DIR "$ENV{HOME}/.config/${PROJECT_NAME}" CACHE PATH "This varialbe contains the path to the games config directory")
debug_report("BP_GAME_CONFIG_DIR = ${BP_GAME_CONFIG_DIR}")


unset(CONFIG_DIR)

