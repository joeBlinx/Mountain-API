cmake_minimum_required(VERSION 3.10)
include(CMakeParseArguments)

add_library(MountainAPI SHARED)
add_library(Mountain::API ALIAS MountainAPI)
set_target_properties(MountainAPI PROPERTIES
		VERSION ${CMAKE_PROJECT_VERSION})

target_include_directories(MountainAPI 
							PUBLIC
		public_inc/
							PRIVATE
		private_inc/mountain
		private_inc/mountain/renderpass
		private_inc/mountain/buffer
		private_inc/mountain/descriptor_setlayout_binding
								)
target_link_libraries(MountainAPI PRIVATE
										vulkan::headers
									PUBLIC
										utils::utils
										window
										CONAN_PKG::stb
										CONAN_PKG::tinyobjloader
										CONAN_PKG::glm
											)

target_compile_definitions(MountainAPI PUBLIC -DGLFW_INCLUDE_VULKAN)
if(${USE_SANITIZER})
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		target_compile_options(MountainAPI PUBLIC $<$<CONFIG:Debug>:-fsanitize=address -fsanitize=undefined>)
		target_link_libraries(MountainAPI PUBLIC "$<$<CONFIG:Debug>:-fsanitize=address -fsanitize=undefined>")
	elseif(MSVC)
		target_compile_options(MountainAPI PUBLIC $<$<CONFIG:Debug>:/fsanitize=address>)
		target_link_libraries(MountainAPI PUBLIC $<$<CONFIG:Debug>:/fsanitize=address>)
	endif()
endif()
target_compile_features(MountainAPI PUBLIC cxx_std_20)
# There must be only one public include
get_target_property(_public_include Mountain::API INTERFACE_INCLUDE_DIRECTORIES)
# If this line failed it's likely that you have more than one public include directory
file(GLOB_RECURSE _public_headers "${_public_include}*.h")
set_target_properties(MountainAPI
		PROPERTIES
		PUBLIC_HEADER "${_public_headers}")

install(
		TARGETS MountainAPI
		CONFIGURATIONS Release
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION bin
		PUBLIC_HEADER DESTINATION include/mountain
)

install(
		FILES ${CMAKE_SOURCE_DIR}/cmake/modules/FindMountainAPI.cmake
		DESTINATION ./

)
set_sources(_srcs
				FOLDER src
				FILES 
					context.cpp
					renderpass/render_pass.cpp
					swapChain.cpp
					command_buffer.cpp
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

set_sources(_headers
		FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/public_inc/mountain
			FILES
				vertex.h
				vertex.tpp
				uniform.h
				image2d.h
				context.h
				render_pass.h
				swapChain.h
				command_buffer.h
				graphics_pipeline.h
				sampler.h
				load_model.h
				no_sanitize.h
			)

target_sources(MountainAPI PRIVATE ${_srcs} ${_srcs_buffer}
							INTERFACE ${_headers})
							