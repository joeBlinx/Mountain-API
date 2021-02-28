add_executable(load_obj)

target_sources(load_obj
		PRIVATE
		main.cpp
		)

set_common_properties(load_obj)

compile_shaders(load_obj
		SHADERS
			triangle.vert
			triangle.frag
		OUTPUT_DIR
			${CMAKE_CURRENT_BINARY_DIR}
		WORKING_DIR
			${CMAKE_CURRENT_SOURCE_DIR}
		)

add_custom_target(copy_assets ALL
		${CMAKE_COMMAND} -E copy_directory  ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
		)
add_dependencies(load_obj copy_assets)

target_compile_definitions(load_obj PRIVATE
		GLM_FORCE_RADIANS
		GLM_FORCE_DEPTH_ZERO_TO_ONE
		)

target_link_libraries(load_obj PRIVATE
									Mountain::API
									CONAN_PKG::glm
											)

