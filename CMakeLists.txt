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

add_custom_target(build_shader ALL
		chmod +x ${PROJECT_SOURCE_DIR}/compile.sh && cp -rf ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}
		COMMAND ${PROJECT_SOURCE_DIR}/compile.sh
		${PROJECT_SOURCE_DIR}/assets/shader ${${PROJECT_NAME}_BINARY_DIR} ${${PROJECT_NAME}_BINARY_DIR})

add_dependencies(sample build_shader)

target_compile_definitions(sample PRIVATE
		GLM_FORCE_RADIANS
		GLM_FORCE_DEPTH_ZERO_TO_ONE
		)
target_include_directories(sample PRIVATE include)

target_link_libraries(sample PRIVATE
											SandBox::utils
											CONAN_PKG::glm
											)

