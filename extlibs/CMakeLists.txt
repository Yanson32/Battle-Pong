file(GLOB_RECURSE BOX2D_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D/*.h")
file(GLOB_RECURSE BOX2D_SOURCES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Box2D/Box2D/*.cpp")

add_library(Box2D STATIC ${BOX2D_HEADER_FILES} ${BOX2D_SOURCES_FILES})
target_include_directories("Box2D" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Box2D")
target_compile_features("Box2D" PUBLIC cxx_nullptr)
