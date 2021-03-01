add_executable(skybox)

target_sources(skybox
		PRIVATE
		main.cpp
		)

set_common_properties(skybox)

compile_shaders(skybox
		SHADERS
		viking.vert
        viking.frag
		OUTPUT_DIR
			${CMAKE_CURRENT_BINARY_DIR}
		WORKING_DIR
			${CMAKE_CURRENT_SOURCE_DIR}
		)


add_dependencies(skybox copy_assets)

target_compile_definitions(skybox PRIVATE
		GLM_FORCE_RADIANS
		GLM_FORCE_DEPTH_ZERO_TO_ONE
		)

target_link_libraries(skybox PRIVATE
									Mountain::API
									CONAN_PKG::glm
											)

