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

add_executable(${PROJECT_NAME})
add_subdirectory(cmake)
add_subdirectory(sandbox_useful)
add_subdirectory(utils)
add_subdirectory(window_management)
target_sources(${PROJECT_NAME} 	
		PRIVATE 
		src/main.cpp
		)

set_common_properties(${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${PROJECT_SOURCE_DIR}/compile.sh
	${PROJECT_SOURCE_DIR}/shader ${${PROJECT_NAME}_BINARY_DIR} ${${PROJECT_NAME}_BINARY_DIR})



target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE
											SandBox::utils
											)

