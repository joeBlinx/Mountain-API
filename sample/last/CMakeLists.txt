add_executable(last)

target_sources(last
		PRIVATE
		main.cpp
		)

set_common_properties(last)

find_program(spriv_compiler glslangValidator)
if(${spriv_compiler} EQUAL glslangValidator_NOTFOUND)
	message(WARNING "glslangValidator executable was not found, shader will not be compiled automatically.
	Don't forget to do it if you want to launch this sample
	")
else()
	file(GLOB shaders assets/shader/*)

	foreach(shader_path ${shaders})
		get_filename_component(shader_name ${shader_path} NAME)
		get_filename_component(shader_extension ${shader_path} EXT)
		get_filename_component(shader_without_extension ${shader_path} NAME_WE)
		string(REPLACE "../.." "" shader_extension ${shader_extension})
		add_custom_target(build_${shader_name} ALL
			${spriv_compiler} -V ${shader_path} #compile shader
			COMMAND
			${CMAKE_COMMAND} -E copy ${shader_extension}.spv ${CMAKE_BINARY_DIR}/${shader_without_extension}${shader_extension}.spv #mv shader to build folder
			)
		add_dependencies(last build_${shader_name})
	endforeach()

	add_custom_target(copy_assets ALL
			${CMAKE_COMMAND} -E copy_directory  ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
			)
	add_dependencies(last copy_assets)
endif()
target_compile_definitions(last PRIVATE
		GLM_FORCE_RADIANS
		GLM_FORCE_DEPTH_ZERO_TO_ONE
		)

target_link_libraries(last PRIVATE
									SandBox::utils
									CONAN_PKG::glm
											)

