cmake_minimum_required(VERSION 3.16)

add_library(common_target INTERFACE)
add_library(common_target::common_target ALIAS common_target)

if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU OR ${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    target_compile_options(common_target INTERFACE -Wall -Wextra -pedantic -Werror)
endif()

add_library(vulkan_headers INTERFACE)
add_library(vulkan::headers ALIAS vulkan_headers)

target_precompile_headers(vulkan_headers
        INTERFACE
        $<BUILD_INTERFACE:vulkan/vulkan.hpp>
        )
target_link_libraries(vulkan_headers INTERFACE Vulkan::Vulkan common_target::common_target)