cmake_minimum_required(VERSION 3.10)
include(cmake/conan.cmake)
include(cmake/utils/utils.cmake)

check_build_type()
project(MOUNTAIN-API
        LANGUAGES CXX
        )
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

option(USE_SDL2 "use sdl2 for window managment" OFF)
option(USE_GLFW "use glfw for window managment" ON)
option(BUILD_SAMPLE "build sample" OFF)
option(BUILD_DOCUMENTATION "build documentation" OFF)
option(USE_SANITIZER "use asan ad ubsan if available" OFF)

message("USE_SDL2 is ${USE_SDL2}")
message("USE_GLFW is ${USE_GLFW}")

download_dependencies()
find_package(Vulkan 1.2 REQUIRED)
add_subdirectory(cmake)
add_subdirectory(mountain)
add_subdirectory(utils)
add_subdirectory(window_management)
if(${BUILD_DOCUMENTATION})
    add_subdirectory(docs)
endif()
if(${BUILD_SAMPLES})
    add_subdirectory(sample)
endif()
