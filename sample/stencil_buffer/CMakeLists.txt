add_executable(stencil_buffer)


compile_shaders(
        stencil_buffer
        SHADERS
            shaders/stencil_buffer.vert
            shaders/stencil_buffer.frag
        OUTPUT_DIR
            ${CMAKE_CURRENT_BINARY_DIR}
        WORKING_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(stencil_buffer
        PRIVATE
            src/main.cpp)