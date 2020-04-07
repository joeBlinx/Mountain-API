cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(cmake/conan.cmake)
include(cmake/utils/utils.cmake)


check_build_type()

project(sandBox
		LANGUAGES CXX
		)

download_dependencies()
find_package(Vulkan REQUIRED)

add_executable(${PROJECT_NAME})
add_subdirectory(cmake)
add_subdirectory(sandbox_useful)
add_subdirectory(utils)
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

