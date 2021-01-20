project(samples)

include(cmake/compile_shader.cmake)


foreach(sample IN ITEMS triangle last)
    set(SHADER_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/${sample})
    set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)
    configure_file(shader_folder.h ${CMAKE_CURRENT_BINARY_DIR}/${sample}/shader_folder.h @ONLY)
    add_subdirectory(${sample})
    target_include_directories(${sample} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${sample})
endforeach()

