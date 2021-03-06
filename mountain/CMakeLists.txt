cmake_minimum_required(VERSION 3.10)
include(CMakeParseArguments)


add_library(MountainAPI SHARED)
add_library(Mountain::API ALIAS MountainAPI)

include(export_header)


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
                                        Mountain::ExportDefinition
                                    PUBLIC
                                        Mountain::ExportFile
										utils::utils
										window
										CONAN_PKG::stb
										CONAN_PKG::tinyobjloader
										CONAN_PKG::glm
											)

target_compile_definitions(MountainAPI
		PUBLIC GLFW_INCLUDE_VULKAN
		)
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

set_sources(_srcs
				FOLDER src
				FILES
					context.cpp
					renderpass/render_pass.cpp
					swapChain.cpp
					command_buffer.cpp
					pipeline/graphics_pipeline.cpp
					pipeline/pipeline_builder.cpp
					buffer/uniform.cpp
					buffer/image2d.cpp
					buffer/vertex.cpp
					descriptor_setlayout_binding/descriptorset_layout.cpp
					sampler.cpp
					load_model.cpp
					present.cpp
			)
set_sources(_srcs_buffer
			FOLDER src/buffer
			FILES
				vertex.cpp)

set_sources(_public_headers
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
				pipeline_builder.h
				descriptorset_layout.h
				sampler.h
				load_model.h
				no_sanitize.h
				subpass.h
				present.h
			)
set(_public_headers ${_public_headers} ${CMAKE_CURRENT_BINARY_DIR}/mountainapi_export.h)

target_sources(MountainAPI PRIVATE ${_srcs} ${_srcs_buffer}
							INTERFACE ${_public_headers})

set_target_properties(MountainAPI
		PROPERTIES
		PUBLIC_HEADER "${_public_headers}" )

install(
		TARGETS MountainAPI
		CONFIGURATIONS Release Debug RelWithDebInfo
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION bin
		PUBLIC_HEADER DESTINATION include/mountain
)

install(
		FILES ${CMAKE_SOURCE_DIR}/cmake/modules/FindMountainAPI.cmake
		DESTINATION ./

)