set(FILES 	"${CMAKE_CURRENT_SOURCE_DIR}/Settings.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/SFMLFunctions.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/TGUIFunctions.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Macros.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Arguments.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ErrorCodes.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/TS_TcpSocket.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/TS_TcpListener.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/TS_String.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/WriteSettings.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/WriteLog.h"

)
set(SUB_DIRECTORIES "Events"
					"Objects"
					"Input"
					"Box2D"
					"Gui"
                    "Resources"
                    "Network"
                    "Engin"
)

#Add subdirectories
foreach(LOOP_VAR ${SUB_DIRECTORIES})
    add_subdirectory("${LOOP_VAR}")
endforeach()

string(REGEX MATCH "include" RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(FILES)
	#Add source file to target
	target_sources(	"${PROJECT_NAME}" PRIVATE ${FILES})
endif()
