
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

macro(check_build_type)
	get_property(_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
	if(NOT ${_multi_config})
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
endmacro()

function(download_dependencies)
	list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/module)
	if(${USE_GLFW})
		set(_window_managment_lib glfw/3.3.2)
		set(_options OPTIONS 
                    glfw/3.3.2:fPIC=True
                    )
	else(${USE_SDL2})
		find_package(SDL2 REQUIRED)
	endif()

	# Download automatically, you can also just copy the conan.cmake file
	if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
		message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
		file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
				"${CMAKE_BINARY_DIR}/conan.cmake"
				TLS_VERIFY ON)
	endif()

	include(${CMAKE_BINARY_DIR}/conan.cmake)

	conan_cmake_run(REQUIRES
			${_window_managment_lib}
			glm/0.9.9.8
			stb/20200203
			tinyobjloader/1.0.6
			BASIC_SETUP CMAKE_TARGETS
			BUILD missing
			${_options})

endfunction()
