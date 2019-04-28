cmake_minimum_required(VERSION 3.14)
project(sandBox
		LANGUAGES CXX)
include(FetchContent)
FetchContent_Declare(
		glfw_content
		GIT_REPOSITORY https://github.com/glfw/glfw.git
		GIT_TAG        3.3
)

find_package(Vulkan REQUIRED)
find_package(glfw3)

if ( NOT TARGET glfw)
	message(glfw is not on your system so it will be download in the build folder)
	FetchContent_MakeAvailable(glfw_content)
endif()

set(OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/executable)

add_executable(${PROJECT_NAME} 	src/main.cpp
		src/initVulkan.cpp include/initVulkan.hpp
		src/log.cpp include/log.hpp
		include/utils.hpp src/utils.cpp
		sandbox_useful/basicInit.hpp
		sandbox_useful/basicInit.cpp
		)

set_target_properties(${PROJECT_NAME}
		PROPERTIES
		CXX_STANDARD 17
		CXX_EXTENSIONS OFF
		RUNTIME_OUTPUT_DIRECTORY  ${OUTPUT_DIRECTORY})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND}
		-E make_directory ${OUTPUT_DIRECTORY})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${PROJECT_SOURCE_DIR}/compile.sh
		${PROJECT_SOURCE_DIR}/shader ${PROJECT_SOURCE_DIR}/executable ${OUTPUT_DIRECTORY})

target_compile_definitions(${PROJECT_NAME} PUBLIC -DGLFW_INCLUDE_VULKAN)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic -Wextra)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)

