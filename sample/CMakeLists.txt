project(samples)

include(cmake/compile_shader.cmake)


foreach(sample IN ITEMS triangle load_obj push_constants textures)
    set(SHADER_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/${sample})
    set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)
    configure_file(ressource_paths.h ${CMAKE_CURRENT_BINARY_DIR}/${sample}/ressource_paths.h @ONLY)
    add_subdirectory(${sample})
    target_include_directories(${sample} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${sample})
endforeach()

