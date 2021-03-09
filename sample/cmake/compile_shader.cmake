# Create custom target to build shader and move it to the output directory specified
# If the output dir doesn't exist, it is created
# Shaders must have their role in extension (.frag, .vert, etc..)
# The output name of the shaders will be <name><role>.spv
# Example: triangle.frag -> trianglefrag.spv
function(compile_shaders target)
        find_program(spriv_compiler glslangValidator)
        if(${spriv_compiler} EQUAL glslangValidator_NOTFOUND)
            message(WARNING "glslangValidator executable was not found, shader will not be compiled automatically.
        Don't forget to do it if you want to launch this sample
        ")
        else()
        set(prefix ARG)
        set(options)
        set(_single_values OUTPUT_DIR WORKING_DIR)
        set(_shaders SHADERS)
        cmake_parse_arguments(${prefix} "${options}" "${_single_values}"
                "${_shaders}" ${ARGN} )
        if(NOT IS_ABSOLUTE ${${prefix}_OUTPUT_DIR})
            set(_output_dir ${${prefix}_WORKING_DIR}/${${prefix}_OUTPUT_DIR})
        else()
            set(_output_dir ${${prefix}_OUTPUT_DIR})
        endif()
        if (NOT EXISTS ${_output_dir})
            file(MAKE_DIRECTORY ${_output_dir})
        endif()
        foreach(shader ${${prefix}_SHADERS})
            if(NOT IS_ABSOLUTE ${shader})
                set(_shader_path ${${prefix}_WORKING_DIR}/${shader})
            else()
                set(_shader_path ${shader})
            endif()
            get_filename_component(shader_name ${_shader_path} NAME)
            get_filename_component(shader_extension ${_shader_path} EXT)
            get_filename_component(shader_without_extension ${_shader_path} NAME_WE)

            string(REPLACE "." "" shader_extension ${shader_extension}) #remove the dot before extension
            message("Creating custom target ${target}_build_${shader_name}")
            add_custom_target(${target}_build_${shader_name} ALL
                    ${spriv_compiler} -V ${_shader_path} -o ${_output_dir}/${shader_without_extension}${shader_extension}.spv #compile shader
                    )
            add_dependencies(${target} ${target}_build_${shader_name})
            set_target_properties(${target}_build_${shader_name} PROPERTIES FOLDER "Samples/${target}/shaders")

        endforeach()
    endif()
endfunction()