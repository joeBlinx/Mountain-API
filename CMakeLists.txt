cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(cmake/conan.cmake)
include(cmake/utils/utils.cmake)


check_build_type()

project(sandBox
		LANGUAGES CXX
		)
option(USE_SDL2 "use sdl2 for window managment" OFF)
option(USE_GLFW "use glfw for window managment" ON)
message("USE_SDL2 is ${USE_SDL2}")
message("USE_GLFW is ${USE_GLFW}")

download_dependencies()
find_package(Vulkan 1.2 REQUIRED)

add_executable(sample)
add_subdirectory(cmake)
add_subdirectory(sandbox_useful)
add_subdirectory(utils)
add_subdirectory(window_management)
target_sources(sample
		PRIVATE 
		src/main.cpp
		)

set_common_properties(sample)

find_program(spriv_compiler glslangValidator)
file(GLOB shaders assets/shader/*)
foreach(shader_path ${shaders})
    get_filename_component(shader_name ${shader_path} NAME)
    get_filename_component(shader_extension ${shader_path} EXT)
    get_filename_component(shader_without_extension ${shader_path} NAME_WE)
    string(REPLACE "." "" shader_extension ${shader_extension})
    add_custom_target(build_${shader_name} ALL
        ${spriv_compiler} -V ${shader_path}
        COMMAND 
        ${CMAKE_COMMAND} -E copy ${shader_extension}.spv ${CMAKE_BINARY_DIR}/${shader_without_extension}${shader_extension}.spv
        )
    add_dependencies(sample build_${shader_name})
endforeach()
add_custom_target(copy_assets ALL 
        ${CMAKE_COMMAND} -E copy_directory  ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
        )
add_dependencies(sample copy_assets)
target_compile_definitions(sample PRIVATE
		GLM_FORCE_RADIANS
		GLM_FORCE_DEPTH_ZERO_TO_ONE
		)
target_include_directories(sample PRIVATE include)

target_link_libraries(sample PRIVATE
											SandBox::utils
											CONAN_PKG::glm
											)

