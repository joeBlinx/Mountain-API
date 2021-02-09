project(samples)

include(cmake/compile_shader.cmake)

set(_samples triangle load_obj push_constants textures)
foreach(sample IN ITEMS ${_samples})
    set(SHADER_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/${sample})
    set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)
    configure_file(ressource_paths.h ${CMAKE_CURRENT_BINARY_DIR}/${sample}/ressource_paths.h @ONLY)
    add_subdirectory(${sample})
    target_include_directories(${sample} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${sample})
endforeach()

add_custom_target(samples ALL) # one target to build all samples
add_dependencies(samples ${_samples})

