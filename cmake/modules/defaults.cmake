include_guard()

#Set default compiler flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -Wall -pedantic" CACHE STRING "Compiler variables for debug mode" FORCE)
endif()

