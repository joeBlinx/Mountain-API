add_executable(push_constants main.cpp)

compile_shaders(push_constants
        SHADERS
            push_constant.vert
            push_constant.frag
        OUTPUT_DIR
            ${CMAKE_CURRENT_BINARY_DIR}
        WORKING_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_link_libraries(push_constants PRIVATE Mountain::API)