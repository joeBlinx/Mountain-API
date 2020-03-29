
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