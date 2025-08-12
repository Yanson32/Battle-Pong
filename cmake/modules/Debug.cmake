
macro(debug_report MSG)
    file(APPEND "${CMAKE_BINARY_DIR}/DebugReport.txt" "${MSG}\n")
    message(VERBOSE "DEBUG REPORT---> ${MSG}")
endmacro()

macro(debug_report_fatal MSG)
    file(APPEND "${CMAKE_BINARY_DIR}/DebugReport.txt" "${MSG}\n")
    message(FATAL_ERROR "${MSG}")
endmacro()


macro(debug_init)
    file(REMOVE "${CMAKE_BINARY_DIR}/DebugReport.txt" "${MSG}\n")
    debug_report("PROJECT_NAME = ${PROJECT_NAME}")
    debug_report("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
    debug_report("Source file = ${CMAKE_CURRENT_LIST_FILE}")
    debug_report("CMake Version ${CMAKE_VERSION}")
    debug_report("CMake c compiler ${CMAKE_C_COMPILER_ID}")
    debug_report("CMake c compiler version ${CMAKE_C_COMPILER_VERSION}")
    debug_report("CMake c++ compiler ${CMAKE_CXX_COMPILER_ID}")
    debug_report("CMake c++ compiler version ${CMAKE_CXX_COMPILER_VERSION}")
    debug_report("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
    debug_report("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
    debug_report("BP_SFML_VERSION = ${BP_SFML_VERSION}")
    debug_report("BP_TGUI_VERSION = ${BP_TGUI_VERSION}")
    debug_report("BP_MATH_VERSION = ${BP_MATH_VERSION}")
    debug_report("BP_GAMEUTILITIES_VERSION = ${GAMEUTILITIES_VERSION}")
    debug_system_info()
endmacro()


macro (debug_system_info)

    set(RELEASE_FILE_PATH "/etc/os-release")
    if(EXISTS "${RELEASE_FILE_PATH}")
        file(STRINGS "${RELEASE_FILE_PATH}" LINES)

        foreach(LINE IN LISTS LINES)
            debug_report("${LINE}")
        endforeach()
    endif()
endmacro()
