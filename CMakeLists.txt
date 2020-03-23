cmake_minimum_required(VERSION 3.14)
project(sandBox
		LANGUAGES CXX)

include(conan.cmake)
conan_cmake_run(REQUIRES glfw/3.3.2@bincrafters/stable BASIC_SETUP CMAKE_TARGETS)
find_package(Vulkan REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} 	PRIVATE src/main.cpp
		src/initVulkan.cpp include/initVulkan.hpp
		src/log.cpp include/log.hpp
		include/utils.hpp src/utils.cpp
		sandbox_useful/basicInit.hpp
		sandbox_useful/basicInit.cpp
		sandbox_useful/device.cpp sandbox_useful/device.hpp sandbox_useful/swapChain.cpp sandbox_useful/swapChain.hpp sandbox_useful/renderpass/renderPass.cpp sandbox_useful/renderpass/renderPass.hpp)

set_target_properties(${PROJECT_NAME}
		PROPERTIES
		CXX_STANDARD 20
		CXX_EXTENSIONS OFF
		)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${PROJECT_SOURCE_DIR}/compile.sh
	${PROJECT_SOURCE_DIR}/shader ${${PROJECT_NAME}_BINARY_DIR} ${${PROJECT_NAME}_BINARY_DIR})

target_compile_definitions(${PROJECT_NAME} PUBLIC -DGLFW_INCLUDE_VULKAN)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic -Wextra)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan CONAN_PKG::glfw)

