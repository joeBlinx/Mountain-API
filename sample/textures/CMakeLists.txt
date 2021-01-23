add_executable(textures main.cpp)

compile_shaders(textures
        SHADERS
        texture.vert
        texture.frag
        OUTPUT_DIR
            ${CMAKE_CURRENT_BINARY_DIR}
        WORKING_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_link_libraries(textures PRIVATE Mountain::API)