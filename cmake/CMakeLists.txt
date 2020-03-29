cmake_minimum_required(VERSION 3.14)

add_library(common_target INTERFACE)
add_library(common_target::common_target ALIAS common_target)

if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU OR ${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    target_compile_options(common_target INTERFACE -Wall -Wextra -pedantic -Werror)
endif()
