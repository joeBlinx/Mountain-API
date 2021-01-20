add_executable(last)

target_sources(last
		PRIVATE
		main.cpp
		)

set_common_properties(last)

compile_shaders(last
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
add_dependencies(last copy_assets)

target_compile_definitions(last PRIVATE
		GLM_FORCE_RADIANS
		GLM_FORCE_DEPTH_ZERO_TO_ONE
		)

target_link_libraries(last PRIVATE
									SandBox::utils
									CONAN_PKG::glm
											)

