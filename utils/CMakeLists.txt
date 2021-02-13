cmake_minimum_required(VERSION 3.14)
add_library(utils STATIC)
add_library(utils::utils ALIAS utils)

set_sources(_srcs 
			FOLDER src
			FILES 
				log.cpp
				utils.cpp)

set_sources(_headers
			FOLDER  ${CMAKE_CURRENT_SOURCE_DIR}/inc/utils
			FILES 
				log.hpp
				utils.hpp
				type_trait.hpp)

set_common_properties(utils)
target_include_directories(utils PRIVATE inc/utils PUBLIC inc/)				
target_link_libraries(utils PUBLIC Vulkan::Vulkan common::target)

set_target_properties(utils PROPERTIES
		POSITION_INDEPENDENT_CODE ON)

target_sources(utils PRIVATE ${_srcs}
					INTERFACE ${_headers}
				)
