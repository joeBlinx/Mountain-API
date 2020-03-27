cmake_minimum_required(VERSION 3.14)
project(sandBox
		LANGUAGES CXX
		)

include(cmake/conan.cmake)
include(cmake/utils.cmake)
conan_cmake_run(REQUIRES glfw/3.3.2@bincrafters/stable BASIC_SETUP CMAKE_TARGETS)
find_package(Vulkan REQUIRED)

add_executable(${PROJECT_NAME})
add_subdirectory(sandbox_useful)
add_subdirectory(utils)
target_sources(${PROJECT_NAME} 	
		PRIVATE 
		src/main.cpp
		src/initVulkan.cpp 
		include/initVulkan.hpp
		)

set_common_properties(${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${PROJECT_SOURCE_DIR}/compile.sh
	${PROJECT_SOURCE_DIR}/shader ${${PROJECT_NAME}_BINARY_DIR} ${${PROJECT_NAME}_BINARY_DIR})

target_compile_definitions(${PROJECT_NAME} PUBLIC -DGLFW_INCLUDE_VULKAN)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic -Wextra)

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan CONAN_PKG::glfw SandBox::utils utils::utils)

