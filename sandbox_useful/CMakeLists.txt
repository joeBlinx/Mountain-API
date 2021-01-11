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
								inc/sandbox_useful/buffer
								)
target_link_libraries(SandBox_utils PRIVATE
										vulkan::headers
									PUBLIC
										utils::utils
										window
										CONAN_PKG::stb
										CONAN_PKG::tinyobjloader
										CONAN_PKG::glm
											)
set_common_properties(SandBox_utils)
set_sources(_srcs
				FOLDER src
				FILES 
					context.cpp
					renderpass/renderPass.cpp
					swapChain.cpp
					initVulkan.cpp
					graphics_pipeline.cpp
					buffer/uniform.cpp
					buffer/image2d.cpp
					descriptor_setlayout_binding/descriptorset_layout.cpp
					sampler.cpp
					load_model.cpp
			)
set_sources(_srcs_buffer
			FOLDER src/buffer
			FILES
				vertex.cpp)
set_sources(_headers_buffer
			FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/inc/sandbox_useful/buffer
			FILES 
				vertex.hpp
				vertex.tpp
				uniform.h
				image2d.h
)			
set_sources(_headers 
				FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/inc/sandbox_useful
				FILES 
					context.hpp
					renderpass/renderPass.hpp
					swapChain.hpp
					initVulkan.hpp
					graphics_pipeline.hpp
					sampler.h
					load_model.h
				)
target_compile_definitions(SandBox_utils PUBLIC -DGLFW_INCLUDE_VULKAN)
target_compile_options(SandBox_utils PUBLIC -fconcepts)
target_sources(SandBox_utils PRIVATE ${_srcs} ${_srcs_buffer}
							INTERFACE ${_headers} ${_headers_buffer})
							