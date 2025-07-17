macro(debug_report MSG)
    file(APPEND "${CMAKE_BINARY_DIR}/DebugReport.txt" "${MSG}\n")
    message(VERBOSE "${MSG}")
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
endmacro()

