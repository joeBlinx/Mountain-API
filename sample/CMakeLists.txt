project(samples)

include(cmake/compile_shader.cmake)
include(cmake/copy_assets.cmake)
add_library(common_sample STATIC common/init.cpp)
target_link_libraries(common_sample PUBLIC common::target Mountain::API)
set(_samples triangle load_obj push_constants textures subrenderpass stencil_buffer)
foreach(sample IN ITEMS ${_samples})
    set(SHADER_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/${sample})
    set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)
    configure_file(ressource_paths.h ${CMAKE_CURRENT_BINARY_DIR}/${sample}/ressource_paths.h @ONLY)
    add_subdirectory(${sample})
    target_include_directories(${sample} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${sample} ./)
    target_link_libraries(${sample} PRIVATE common_sample)
    set_target_properties(${sample} PROPERTIES FOLDER "Samples/${sample}")

endforeach()

add_custom_target(samples ALL) # one target to build all samples
add_dependencies(samples ${_samples})
set_target_properties(samples PROPERTIES FOLDER "Samples")


