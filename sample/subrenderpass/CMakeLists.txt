add_executable(subrenderpass)

target_sources(subrenderpass
		PRIVATE
		src/main.cpp
		src/init.cpp
		src/init.h
		)

set_common_properties(subrenderpass)

compile_shaders(subrenderpass
		SHADERS
		shaders/viking.vert
		shaders/viking.frag
		shaders/portrait.frag
		shaders/portrait.vert
		OUTPUT_DIR
			${CMAKE_CURRENT_BINARY_DIR}
		WORKING_DIR
			${CMAKE_CURRENT_SOURCE_DIR}
		)


add_dependencies(subrenderpass copy_assets)

target_compile_definitions(subrenderpass PRIVATE
		GLM_FORCE_RADIANS
		GLM_FORCE_DEPTH_ZERO_TO_ONE
		)

target_link_libraries(subrenderpass PRIVATE
									Mountain::API
									CONAN_PKG::glm
											)

