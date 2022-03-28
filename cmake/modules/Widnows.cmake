set(CONFIG_DIR "$ENV{CSIDL_DEFAULT_APPDATA}/${PROJECT_NAME}")
message("Resources will be installed into ${CONFIG_DIR} Folder")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources/" DESTINATION "${CONFIG_DIR}")
target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCE_INSTALL_PATH="${CONFIG_DIR}")
unset(CONFIG_DIR)

