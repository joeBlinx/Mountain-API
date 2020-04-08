
function(set_sources out_var)
	set(prefix ARG)
	set(no_values "")
	set(single_values FOLDER)
	set(multiple_values FILES)

	cmake_parse_arguments(${prefix} "${no_values}" "${single_values}" "${multiple_values}" ${ARGN}) 
	set(folder ${${prefix}_FOLDER})
	foreach(file IN LISTS ${prefix}_FILES)
		list(APPEND sources ${folder}/${file})	
	endforeach()
	set(${out_var} ${sources} PARENT_SCOPE)
endfunction()


macro(set_common_properties target)
	set_target_properties(${target} PROPERTIES
							CXX_STANDARD 20
							CXX_EXTENSIONS OFF)		
endmacro()

function(check_build_type)
	if(NOT GENERATOR_IS_MULTI_CONFIG)
		set(available_build_type Debug Release)
		if(NOT ${CMAKE_BUILD_TYPE} IN_LIST available_build_type)
			message(SEND_ERROR "Only Debug and Release are allowed")
			return()
		else()
			if("${CMAKE_BUILD_TYPE}" STREQUAL "")
				message(WARNING "No build type as been specified, it will be Debug by default")
				set(CMAKE_BUILD_TYPE Debug)
			endif()
			message(STATUS "BUILD TYPE : ${CMAKE_BUILD_TYPE}")
		endif()
	endif()
endfunction()

function(download_dependencies)
	include(FetchContent)
	FetchContent_Declare(
			glfw_content
			GIT_REPOSITORY https://github.com/glfw/glfw.git
			GIT_TAG        3.3
	)

	message(STATUS "DOWNLOAD : GLFW3")
	FetchContent_MakeAvailable(glfw_content)
endfunction()