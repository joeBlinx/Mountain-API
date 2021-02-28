add_custom_target(copy_assets ALL
        ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
        )