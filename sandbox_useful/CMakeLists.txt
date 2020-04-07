cmake_minimum_required(VERSION 3.10)
include(CMakeParseArguments)


add_library(SandBox_utils STATIC)
add_library(SandBox::utils ALIAS SandBox_utils)

target_include_directories(SandBox_utils 
							PUBLIC 
								inc/ 
							PRIVATE 
								inc/sandbox_useful 
								inc/sandbox_useful/renderpass
								)
target_link_libraries(SandBox_utils PRIVATE 																						vulkan::headers
									PUBLIC
										utils::utils
										glfw
											)
set_common_properties(SandBox_utils)
set_sources(_srcs
				FOLDER src
				FILES 
					basicInit.cpp
					device.cpp
					renderpass/renderPass.cpp
					swapChain.cpp
					initVulkan.cpp
			)
set_sources(_headers 
				FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/inc/sandbox_useful
				FILES 
					basicInit.hpp
					device.hpp
					renderpass/renderPass.hpp
					swapChain.hpp
					initVulkan.hpp
				)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DGLFW_INCLUDE_VULKAN)
target_sources(SandBox_utils PRIVATE ${_srcs} 
							INTERFACE ${_headers})