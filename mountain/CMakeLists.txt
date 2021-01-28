cmake_minimum_required(VERSION 3.10)
include(CMakeParseArguments)


add_library(Mountain_API STATIC)
add_library(Mountain::API ALIAS Mountain_API)

target_include_directories(Mountain_API 
							PUBLIC 
								inc/ 
							PRIVATE
		inc/mountain
		inc/mountain/renderpass
		inc/mountain/buffer
								)
target_link_libraries(Mountain_API PRIVATE
										vulkan::headers
									PUBLIC
										utils::utils
										window
										CONAN_PKG::stb
										CONAN_PKG::tinyobjloader
										CONAN_PKG::glm
											)

target_compile_definitions(Mountain_API PUBLIC -DGLFW_INCLUDE_VULKAN)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	target_compile_options(Mountain_API PRIVATE $<$<CONFIG:Debug>:-fsanitize=address  -fsanitize=undefined>)
	target_link_libraries(Mountain_API PRIVATE $<$<CONFIG:Debug>:-fsanitize=address -fsanitize=undefined>)
elseif(MSVC)
	target_compile_options(Mountain_API PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
	target_link_libraries(Mountain_API PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
endif()
set_common_properties(Mountain_API)
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
			FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/inc/mountain/buffer
			FILES 
				vertex.hpp
				vertex.tpp
				uniform.h
				image2d.h
)			
set_sources(_headers 
				FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/inc/mountain
				FILES 
					context.hpp
					renderpass/renderPass.hpp
					swapChain.hpp
					initVulkan.hpp
					graphics_pipeline.hpp
					sampler.h
					load_model.h
				)

target_sources(Mountain_API PRIVATE ${_srcs} ${_srcs_buffer}
							INTERFACE ${_headers} ${_headers_buffer})
							