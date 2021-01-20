add_executable(triangle main.cpp)

compile_shaders(triangle
        SHADERS
            triangle.vert
            triangle.frag
        OUTPUT_DIR
            ${CMAKE_CURRENT_BINARY_DIR}
        WORKING_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_link_libraries(triangle PRIVATE Mountain::API)