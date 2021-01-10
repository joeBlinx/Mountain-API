cmake_minimum_required(VERSION 3.16)


add_library(window STATIC)
target_link_libraries(window PUBLIC utils
        PRIVATE common_target::common_target)
target_include_directories(window
        PUBLIC
            .
        )
if(${USE_GLFW})
    target_compile_definitions(window
            PUBLIC
                USE_GLFW
                GLFW_INCLUDE_VULKAN)
    target_sources(window
            PRIVATE
            glfw/window.cpp
            glfw/window.h)
    target_link_libraries(window PUBLIC CONAN_PKG::glfw)
elseif(${USE_SDL2})
    target_compile_definitions(window
            PUBLIC
            USE_SDL2
            )
    target_sources(window
            PRIVATE
            sdl2/window.cpp
            sdl2/window.h)
    target_link_libraries(window PUBLIC SDL2::Main)
endif()