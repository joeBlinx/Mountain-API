include(CMakeParseArguments)

macro(conan_find_apple_frameworks FRAMEWORKS_FOUND FRAMEWORKS SUFFIX)
    if(APPLE)
        if(CMAKE_BUILD_TYPE)
            if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_DEBUG} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS${SUFFIX}_DEBUG} ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_RELEASE} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS${SUFFIX}_RELEASE} ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            elseif(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_RELWITHDEBINFO} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS_RELWITHDEBINFO} ${CONAN_FRAMEWORK_DIRS})
            elseif(${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_MINSIZEREL} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS${SUFFIX}_MINSIZEREL} ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            endif()
        endif()
        foreach(_FRAMEWORK ${FRAMEWORKS})
            # https://cmake.org/pipermail/cmake-developers/2017-August/030199.html
            find_library(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND NAME ${_FRAMEWORK} PATHS ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            if(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND)
                list(APPEND ${FRAMEWORKS_FOUND} ${CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND})
            else()
                message(FATAL_ERROR "Framework library ${_FRAMEWORK} not found in paths: ${CONAN_FRAMEWORK_DIRS${SUFFIX}}")
            endif()
        endforeach()
    endif()
endmacro()


#################
###  GLFW
#################
set(CONAN_GLFW_ROOT "/home/user/.conan/data/glfw/3.3.2/bincrafters/stable/package/6a0b195b06ef5fbc1ca4422976fe500aeb5bab2c")
set(CONAN_INCLUDE_DIRS_GLFW "/home/user/.conan/data/glfw/3.3.2/bincrafters/stable/package/6a0b195b06ef5fbc1ca4422976fe500aeb5bab2c/include")
set(CONAN_LIB_DIRS_GLFW "/home/user/.conan/data/glfw/3.3.2/bincrafters/stable/package/6a0b195b06ef5fbc1ca4422976fe500aeb5bab2c/lib")
set(CONAN_BIN_DIRS_GLFW )
set(CONAN_RES_DIRS_GLFW )
set(CONAN_SRC_DIRS_GLFW )
set(CONAN_BUILD_DIRS_GLFW "/home/user/.conan/data/glfw/3.3.2/bincrafters/stable/package/6a0b195b06ef5fbc1ca4422976fe500aeb5bab2c/")
set(CONAN_FRAMEWORK_DIRS_GLFW )
set(CONAN_LIBS_GLFW glfw3)
set(CONAN_PKG_LIBS_GLFW glfw3)
set(CONAN_SYSTEM_LIBS_GLFW m dl pthread)
set(CONAN_FRAMEWORKS_GLFW )
set(CONAN_FRAMEWORKS_FOUND_GLFW "")  # Will be filled later
set(CONAN_DEFINES_GLFW )
set(CONAN_BUILD_MODULES_PATHS_GLFW )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_GLFW )

set(CONAN_C_FLAGS_GLFW "")
set(CONAN_CXX_FLAGS_GLFW "")
set(CONAN_SHARED_LINKER_FLAGS_GLFW "")
set(CONAN_EXE_LINKER_FLAGS_GLFW "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_GLFW_LIST "")
set(CONAN_CXX_FLAGS_GLFW_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_GLFW_LIST "")
set(CONAN_EXE_LINKER_FLAGS_GLFW_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_GLFW "${CONAN_FRAMEWORKS_GLFW}" "_GLFW")
# Append to aggregated values variable
set(CONAN_LIBS_GLFW ${CONAN_PKG_LIBS_GLFW} ${CONAN_SYSTEM_LIBS_GLFW} ${CONAN_FRAMEWORKS_FOUND_GLFW})


#################
###  LIBXINERAMA
#################
set(CONAN_LIBXINERAMA_ROOT "/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56")
set(CONAN_INCLUDE_DIRS_LIBXINERAMA "/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/include")
set(CONAN_LIB_DIRS_LIBXINERAMA "/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib")
set(CONAN_BIN_DIRS_LIBXINERAMA )
set(CONAN_RES_DIRS_LIBXINERAMA )
set(CONAN_SRC_DIRS_LIBXINERAMA )
set(CONAN_BUILD_DIRS_LIBXINERAMA "/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/"
			"/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXINERAMA )
set(CONAN_LIBS_LIBXINERAMA Xinerama)
set(CONAN_PKG_LIBS_LIBXINERAMA Xinerama)
set(CONAN_SYSTEM_LIBS_LIBXINERAMA )
set(CONAN_FRAMEWORKS_LIBXINERAMA )
set(CONAN_FRAMEWORKS_FOUND_LIBXINERAMA "")  # Will be filled later
set(CONAN_DEFINES_LIBXINERAMA )
set(CONAN_BUILD_MODULES_PATHS_LIBXINERAMA )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXINERAMA )

set(CONAN_C_FLAGS_LIBXINERAMA "")
set(CONAN_CXX_FLAGS_LIBXINERAMA "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXINERAMA "")
set(CONAN_EXE_LINKER_FLAGS_LIBXINERAMA "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXINERAMA_LIST "")
set(CONAN_CXX_FLAGS_LIBXINERAMA_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXINERAMA_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXINERAMA_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXINERAMA "${CONAN_FRAMEWORKS_LIBXINERAMA}" "_LIBXINERAMA")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXINERAMA ${CONAN_PKG_LIBS_LIBXINERAMA} ${CONAN_SYSTEM_LIBS_LIBXINERAMA} ${CONAN_FRAMEWORKS_FOUND_LIBXINERAMA})


#################
###  LIBXCURSOR
#################
set(CONAN_LIBXCURSOR_ROOT "/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7")
set(CONAN_INCLUDE_DIRS_LIBXCURSOR "/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/include")
set(CONAN_LIB_DIRS_LIBXCURSOR "/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/lib")
set(CONAN_BIN_DIRS_LIBXCURSOR )
set(CONAN_RES_DIRS_LIBXCURSOR )
set(CONAN_SRC_DIRS_LIBXCURSOR )
set(CONAN_BUILD_DIRS_LIBXCURSOR "/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/"
			"/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXCURSOR )
set(CONAN_LIBS_LIBXCURSOR Xcursor)
set(CONAN_PKG_LIBS_LIBXCURSOR Xcursor)
set(CONAN_SYSTEM_LIBS_LIBXCURSOR )
set(CONAN_FRAMEWORKS_LIBXCURSOR )
set(CONAN_FRAMEWORKS_FOUND_LIBXCURSOR "")  # Will be filled later
set(CONAN_DEFINES_LIBXCURSOR )
set(CONAN_BUILD_MODULES_PATHS_LIBXCURSOR )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXCURSOR )

set(CONAN_C_FLAGS_LIBXCURSOR "")
set(CONAN_CXX_FLAGS_LIBXCURSOR "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXCURSOR "")
set(CONAN_EXE_LINKER_FLAGS_LIBXCURSOR "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXCURSOR_LIST "")
set(CONAN_CXX_FLAGS_LIBXCURSOR_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXCURSOR_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXCURSOR_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXCURSOR "${CONAN_FRAMEWORKS_LIBXCURSOR}" "_LIBXCURSOR")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXCURSOR ${CONAN_PKG_LIBS_LIBXCURSOR} ${CONAN_SYSTEM_LIBS_LIBXCURSOR} ${CONAN_FRAMEWORKS_FOUND_LIBXCURSOR})


#################
###  LIBXI
#################
set(CONAN_LIBXI_ROOT "/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56")
set(CONAN_INCLUDE_DIRS_LIBXI "/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/include")
set(CONAN_LIB_DIRS_LIBXI "/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib")
set(CONAN_BIN_DIRS_LIBXI )
set(CONAN_RES_DIRS_LIBXI )
set(CONAN_SRC_DIRS_LIBXI )
set(CONAN_BUILD_DIRS_LIBXI "/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/"
			"/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXI )
set(CONAN_LIBS_LIBXI Xi)
set(CONAN_PKG_LIBS_LIBXI Xi)
set(CONAN_SYSTEM_LIBS_LIBXI )
set(CONAN_FRAMEWORKS_LIBXI )
set(CONAN_FRAMEWORKS_FOUND_LIBXI "")  # Will be filled later
set(CONAN_DEFINES_LIBXI )
set(CONAN_BUILD_MODULES_PATHS_LIBXI )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXI )

set(CONAN_C_FLAGS_LIBXI "")
set(CONAN_CXX_FLAGS_LIBXI "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXI "")
set(CONAN_EXE_LINKER_FLAGS_LIBXI "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXI_LIST "")
set(CONAN_CXX_FLAGS_LIBXI_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXI_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXI_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXI "${CONAN_FRAMEWORKS_LIBXI}" "_LIBXI")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXI ${CONAN_PKG_LIBS_LIBXI} ${CONAN_SYSTEM_LIBS_LIBXI} ${CONAN_FRAMEWORKS_FOUND_LIBXI})


#################
###  MESA
#################
set(CONAN_MESA_ROOT "/home/user/.conan/data/mesa/19.3.1/bincrafters/stable/package/4738ebe557ba170d04ecce21fcb989f0bce5f442")
set(CONAN_INCLUDE_DIRS_MESA "/home/user/.conan/data/mesa/19.3.1/bincrafters/stable/package/4738ebe557ba170d04ecce21fcb989f0bce5f442/include")
set(CONAN_LIB_DIRS_MESA "/home/user/.conan/data/mesa/19.3.1/bincrafters/stable/package/4738ebe557ba170d04ecce21fcb989f0bce5f442/lib")
set(CONAN_BIN_DIRS_MESA )
set(CONAN_RES_DIRS_MESA )
set(CONAN_SRC_DIRS_MESA )
set(CONAN_BUILD_DIRS_MESA "/home/user/.conan/data/mesa/19.3.1/bincrafters/stable/package/4738ebe557ba170d04ecce21fcb989f0bce5f442/")
set(CONAN_FRAMEWORK_DIRS_MESA )
set(CONAN_LIBS_MESA EGL GL gbm glapi vulkan_intel)
set(CONAN_PKG_LIBS_MESA EGL GL gbm glapi vulkan_intel)
set(CONAN_SYSTEM_LIBS_MESA )
set(CONAN_FRAMEWORKS_MESA )
set(CONAN_FRAMEWORKS_FOUND_MESA "")  # Will be filled later
set(CONAN_DEFINES_MESA )
set(CONAN_BUILD_MODULES_PATHS_MESA )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_MESA )

set(CONAN_C_FLAGS_MESA "")
set(CONAN_CXX_FLAGS_MESA "")
set(CONAN_SHARED_LINKER_FLAGS_MESA "")
set(CONAN_EXE_LINKER_FLAGS_MESA "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_MESA_LIST "")
set(CONAN_CXX_FLAGS_MESA_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_MESA_LIST "")
set(CONAN_EXE_LINKER_FLAGS_MESA_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_MESA "${CONAN_FRAMEWORKS_MESA}" "_MESA")
# Append to aggregated values variable
set(CONAN_LIBS_MESA ${CONAN_PKG_LIBS_MESA} ${CONAN_SYSTEM_LIBS_MESA} ${CONAN_FRAMEWORKS_FOUND_MESA})


#################
###  LIBXRANDR
#################
set(CONAN_LIBXRANDR_ROOT "/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3")
set(CONAN_INCLUDE_DIRS_LIBXRANDR "/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/include")
set(CONAN_LIB_DIRS_LIBXRANDR "/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/lib")
set(CONAN_BIN_DIRS_LIBXRANDR )
set(CONAN_RES_DIRS_LIBXRANDR )
set(CONAN_SRC_DIRS_LIBXRANDR )
set(CONAN_BUILD_DIRS_LIBXRANDR "/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/"
			"/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXRANDR )
set(CONAN_LIBS_LIBXRANDR Xrandr)
set(CONAN_PKG_LIBS_LIBXRANDR Xrandr)
set(CONAN_SYSTEM_LIBS_LIBXRANDR )
set(CONAN_FRAMEWORKS_LIBXRANDR )
set(CONAN_FRAMEWORKS_FOUND_LIBXRANDR "")  # Will be filled later
set(CONAN_DEFINES_LIBXRANDR )
set(CONAN_BUILD_MODULES_PATHS_LIBXRANDR )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXRANDR )

set(CONAN_C_FLAGS_LIBXRANDR "")
set(CONAN_CXX_FLAGS_LIBXRANDR "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXRANDR "")
set(CONAN_EXE_LINKER_FLAGS_LIBXRANDR "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXRANDR_LIST "")
set(CONAN_CXX_FLAGS_LIBXRANDR_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXRANDR_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXRANDR_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXRANDR "${CONAN_FRAMEWORKS_LIBXRANDR}" "_LIBXRANDR")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXRANDR ${CONAN_PKG_LIBS_LIBXRANDR} ${CONAN_SYSTEM_LIBS_LIBXRANDR} ${CONAN_FRAMEWORKS_FOUND_LIBXRANDR})


#################
###  ZLIB
#################
set(CONAN_ZLIB_ROOT "/home/user/.conan/data/zlib/1.2.11/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8")
set(CONAN_INCLUDE_DIRS_ZLIB "/home/user/.conan/data/zlib/1.2.11/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include")
set(CONAN_LIB_DIRS_ZLIB "/home/user/.conan/data/zlib/1.2.11/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib")
set(CONAN_BIN_DIRS_ZLIB )
set(CONAN_RES_DIRS_ZLIB )
set(CONAN_SRC_DIRS_ZLIB )
set(CONAN_BUILD_DIRS_ZLIB "/home/user/.conan/data/zlib/1.2.11/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/")
set(CONAN_FRAMEWORK_DIRS_ZLIB )
set(CONAN_LIBS_ZLIB z)
set(CONAN_PKG_LIBS_ZLIB z)
set(CONAN_SYSTEM_LIBS_ZLIB )
set(CONAN_FRAMEWORKS_ZLIB )
set(CONAN_FRAMEWORKS_FOUND_ZLIB "")  # Will be filled later
set(CONAN_DEFINES_ZLIB )
set(CONAN_BUILD_MODULES_PATHS_ZLIB )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_ZLIB )

set(CONAN_C_FLAGS_ZLIB "")
set(CONAN_CXX_FLAGS_ZLIB "")
set(CONAN_SHARED_LINKER_FLAGS_ZLIB "")
set(CONAN_EXE_LINKER_FLAGS_ZLIB "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_ZLIB_LIST "")
set(CONAN_CXX_FLAGS_ZLIB_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_ZLIB_LIST "")
set(CONAN_EXE_LINKER_FLAGS_ZLIB_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_ZLIB "${CONAN_FRAMEWORKS_ZLIB}" "_ZLIB")
# Append to aggregated values variable
set(CONAN_LIBS_ZLIB ${CONAN_PKG_LIBS_ZLIB} ${CONAN_SYSTEM_LIBS_ZLIB} ${CONAN_FRAMEWORKS_FOUND_ZLIB})


#################
###  EXPAT
#################
set(CONAN_EXPAT_ROOT "/home/user/.conan/data/expat/2.2.9/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8")
set(CONAN_INCLUDE_DIRS_EXPAT "/home/user/.conan/data/expat/2.2.9/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include")
set(CONAN_LIB_DIRS_EXPAT "/home/user/.conan/data/expat/2.2.9/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib")
set(CONAN_BIN_DIRS_EXPAT )
set(CONAN_RES_DIRS_EXPAT )
set(CONAN_SRC_DIRS_EXPAT )
set(CONAN_BUILD_DIRS_EXPAT "/home/user/.conan/data/expat/2.2.9/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/")
set(CONAN_FRAMEWORK_DIRS_EXPAT )
set(CONAN_LIBS_EXPAT expat)
set(CONAN_PKG_LIBS_EXPAT expat)
set(CONAN_SYSTEM_LIBS_EXPAT )
set(CONAN_FRAMEWORKS_EXPAT )
set(CONAN_FRAMEWORKS_FOUND_EXPAT "")  # Will be filled later
set(CONAN_DEFINES_EXPAT "-DXML_STATIC")
set(CONAN_BUILD_MODULES_PATHS_EXPAT )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_EXPAT "XML_STATIC")

set(CONAN_C_FLAGS_EXPAT "")
set(CONAN_CXX_FLAGS_EXPAT "")
set(CONAN_SHARED_LINKER_FLAGS_EXPAT "")
set(CONAN_EXE_LINKER_FLAGS_EXPAT "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_EXPAT_LIST "")
set(CONAN_CXX_FLAGS_EXPAT_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_EXPAT_LIST "")
set(CONAN_EXE_LINKER_FLAGS_EXPAT_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_EXPAT "${CONAN_FRAMEWORKS_EXPAT}" "_EXPAT")
# Append to aggregated values variable
set(CONAN_LIBS_EXPAT ${CONAN_PKG_LIBS_EXPAT} ${CONAN_SYSTEM_LIBS_EXPAT} ${CONAN_FRAMEWORKS_FOUND_EXPAT})


#################
###  LIBDRM
#################
set(CONAN_LIBDRM_ROOT "/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168")
set(CONAN_INCLUDE_DIRS_LIBDRM "/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/include"
			"/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/include/libdrm"
			"/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/include/libkms")
set(CONAN_LIB_DIRS_LIBDRM "/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/lib")
set(CONAN_BIN_DIRS_LIBDRM )
set(CONAN_RES_DIRS_LIBDRM )
set(CONAN_SRC_DIRS_LIBDRM )
set(CONAN_BUILD_DIRS_LIBDRM "/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/")
set(CONAN_FRAMEWORK_DIRS_LIBDRM )
set(CONAN_LIBS_LIBDRM drm drm_amdgpu drm_freedreno drm_intel drm_nouveau drm_radeon kms)
set(CONAN_PKG_LIBS_LIBDRM drm drm_amdgpu drm_freedreno drm_intel drm_nouveau drm_radeon kms)
set(CONAN_SYSTEM_LIBS_LIBDRM )
set(CONAN_FRAMEWORKS_LIBDRM )
set(CONAN_FRAMEWORKS_FOUND_LIBDRM "")  # Will be filled later
set(CONAN_DEFINES_LIBDRM )
set(CONAN_BUILD_MODULES_PATHS_LIBDRM )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBDRM )

set(CONAN_C_FLAGS_LIBDRM "")
set(CONAN_CXX_FLAGS_LIBDRM "")
set(CONAN_SHARED_LINKER_FLAGS_LIBDRM "")
set(CONAN_EXE_LINKER_FLAGS_LIBDRM "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBDRM_LIST "")
set(CONAN_CXX_FLAGS_LIBDRM_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBDRM_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBDRM_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBDRM "${CONAN_FRAMEWORKS_LIBDRM}" "_LIBDRM")
# Append to aggregated values variable
set(CONAN_LIBS_LIBDRM ${CONAN_PKG_LIBS_LIBDRM} ${CONAN_SYSTEM_LIBS_LIBDRM} ${CONAN_FRAMEWORKS_FOUND_LIBDRM})


#################
###  LIBELF
#################
set(CONAN_LIBELF_ROOT "/home/user/.conan/data/libelf/0.8.13/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8")
set(CONAN_INCLUDE_DIRS_LIBELF "/home/user/.conan/data/libelf/0.8.13/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include")
set(CONAN_LIB_DIRS_LIBELF "/home/user/.conan/data/libelf/0.8.13/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib")
set(CONAN_BIN_DIRS_LIBELF )
set(CONAN_RES_DIRS_LIBELF )
set(CONAN_SRC_DIRS_LIBELF )
set(CONAN_BUILD_DIRS_LIBELF "/home/user/.conan/data/libelf/0.8.13/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/")
set(CONAN_FRAMEWORK_DIRS_LIBELF )
set(CONAN_LIBS_LIBELF elf)
set(CONAN_PKG_LIBS_LIBELF elf)
set(CONAN_SYSTEM_LIBS_LIBELF )
set(CONAN_FRAMEWORKS_LIBELF )
set(CONAN_FRAMEWORKS_FOUND_LIBELF "")  # Will be filled later
set(CONAN_DEFINES_LIBELF )
set(CONAN_BUILD_MODULES_PATHS_LIBELF )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBELF )

set(CONAN_C_FLAGS_LIBELF "")
set(CONAN_CXX_FLAGS_LIBELF "")
set(CONAN_SHARED_LINKER_FLAGS_LIBELF "")
set(CONAN_EXE_LINKER_FLAGS_LIBELF "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBELF_LIST "")
set(CONAN_CXX_FLAGS_LIBELF_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBELF_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBELF_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBELF "${CONAN_FRAMEWORKS_LIBELF}" "_LIBELF")
# Append to aggregated values variable
set(CONAN_LIBS_LIBELF ${CONAN_PKG_LIBS_LIBELF} ${CONAN_SYSTEM_LIBS_LIBELF} ${CONAN_FRAMEWORKS_FOUND_LIBELF})


#################
###  LIBUNWIND
#################
set(CONAN_LIBUNWIND_ROOT "/home/user/.conan/data/libunwind/1.3.1/_/_/package/eef58b252f2cfddca30f2e8758005c7d67542d8a")
set(CONAN_INCLUDE_DIRS_LIBUNWIND "/home/user/.conan/data/libunwind/1.3.1/_/_/package/eef58b252f2cfddca30f2e8758005c7d67542d8a/include")
set(CONAN_LIB_DIRS_LIBUNWIND "/home/user/.conan/data/libunwind/1.3.1/_/_/package/eef58b252f2cfddca30f2e8758005c7d67542d8a/lib")
set(CONAN_BIN_DIRS_LIBUNWIND )
set(CONAN_RES_DIRS_LIBUNWIND )
set(CONAN_SRC_DIRS_LIBUNWIND )
set(CONAN_BUILD_DIRS_LIBUNWIND "/home/user/.conan/data/libunwind/1.3.1/_/_/package/eef58b252f2cfddca30f2e8758005c7d67542d8a/")
set(CONAN_FRAMEWORK_DIRS_LIBUNWIND )
set(CONAN_LIBS_LIBUNWIND unwind unwind-coredump unwind-generic unwind-ptrace unwind-setjmp unwind-x86_64)
set(CONAN_PKG_LIBS_LIBUNWIND unwind unwind-coredump unwind-generic unwind-ptrace unwind-setjmp unwind-x86_64)
set(CONAN_SYSTEM_LIBS_LIBUNWIND pthread)
set(CONAN_FRAMEWORKS_LIBUNWIND )
set(CONAN_FRAMEWORKS_FOUND_LIBUNWIND "")  # Will be filled later
set(CONAN_DEFINES_LIBUNWIND )
set(CONAN_BUILD_MODULES_PATHS_LIBUNWIND )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBUNWIND )

set(CONAN_C_FLAGS_LIBUNWIND "")
set(CONAN_CXX_FLAGS_LIBUNWIND "")
set(CONAN_SHARED_LINKER_FLAGS_LIBUNWIND "")
set(CONAN_EXE_LINKER_FLAGS_LIBUNWIND "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBUNWIND_LIST "")
set(CONAN_CXX_FLAGS_LIBUNWIND_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBUNWIND_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBUNWIND "${CONAN_FRAMEWORKS_LIBUNWIND}" "_LIBUNWIND")
# Append to aggregated values variable
set(CONAN_LIBS_LIBUNWIND ${CONAN_PKG_LIBS_LIBUNWIND} ${CONAN_SYSTEM_LIBS_LIBUNWIND} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND})


#################
###  LIBXDAMAGE
#################
set(CONAN_LIBXDAMAGE_ROOT "/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6")
set(CONAN_INCLUDE_DIRS_LIBXDAMAGE "/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/include")
set(CONAN_LIB_DIRS_LIBXDAMAGE "/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/lib")
set(CONAN_BIN_DIRS_LIBXDAMAGE )
set(CONAN_RES_DIRS_LIBXDAMAGE )
set(CONAN_SRC_DIRS_LIBXDAMAGE )
set(CONAN_BUILD_DIRS_LIBXDAMAGE "/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/"
			"/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXDAMAGE )
set(CONAN_LIBS_LIBXDAMAGE Xdamage)
set(CONAN_PKG_LIBS_LIBXDAMAGE Xdamage)
set(CONAN_SYSTEM_LIBS_LIBXDAMAGE )
set(CONAN_FRAMEWORKS_LIBXDAMAGE )
set(CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE "")  # Will be filled later
set(CONAN_DEFINES_LIBXDAMAGE )
set(CONAN_BUILD_MODULES_PATHS_LIBXDAMAGE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXDAMAGE )

set(CONAN_C_FLAGS_LIBXDAMAGE "")
set(CONAN_CXX_FLAGS_LIBXDAMAGE "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXDAMAGE "")
set(CONAN_EXE_LINKER_FLAGS_LIBXDAMAGE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXDAMAGE_LIST "")
set(CONAN_CXX_FLAGS_LIBXDAMAGE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXDAMAGE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXDAMAGE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE "${CONAN_FRAMEWORKS_LIBXDAMAGE}" "_LIBXDAMAGE")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXDAMAGE ${CONAN_PKG_LIBS_LIBXDAMAGE} ${CONAN_SYSTEM_LIBS_LIBXDAMAGE} ${CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE})


#################
###  LIBXSHMFENCE
#################
set(CONAN_LIBXSHMFENCE_ROOT "/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660")
set(CONAN_INCLUDE_DIRS_LIBXSHMFENCE "/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/include")
set(CONAN_LIB_DIRS_LIBXSHMFENCE "/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/lib")
set(CONAN_BIN_DIRS_LIBXSHMFENCE )
set(CONAN_RES_DIRS_LIBXSHMFENCE )
set(CONAN_SRC_DIRS_LIBXSHMFENCE )
set(CONAN_BUILD_DIRS_LIBXSHMFENCE "/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/"
			"/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXSHMFENCE )
set(CONAN_LIBS_LIBXSHMFENCE xshmfence)
set(CONAN_PKG_LIBS_LIBXSHMFENCE xshmfence)
set(CONAN_SYSTEM_LIBS_LIBXSHMFENCE )
set(CONAN_FRAMEWORKS_LIBXSHMFENCE )
set(CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE "")  # Will be filled later
set(CONAN_DEFINES_LIBXSHMFENCE )
set(CONAN_BUILD_MODULES_PATHS_LIBXSHMFENCE )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXSHMFENCE )

set(CONAN_C_FLAGS_LIBXSHMFENCE "")
set(CONAN_CXX_FLAGS_LIBXSHMFENCE "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXSHMFENCE "")
set(CONAN_EXE_LINKER_FLAGS_LIBXSHMFENCE "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXSHMFENCE_LIST "")
set(CONAN_CXX_FLAGS_LIBXSHMFENCE_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXSHMFENCE_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXSHMFENCE_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE "${CONAN_FRAMEWORKS_LIBXSHMFENCE}" "_LIBXSHMFENCE")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXSHMFENCE ${CONAN_PKG_LIBS_LIBXSHMFENCE} ${CONAN_SYSTEM_LIBS_LIBXSHMFENCE} ${CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE})


#################
###  LIBXXF86VM
#################
set(CONAN_LIBXXF86VM_ROOT "/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836")
set(CONAN_INCLUDE_DIRS_LIBXXF86VM "/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/include")
set(CONAN_LIB_DIRS_LIBXXF86VM "/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/lib")
set(CONAN_BIN_DIRS_LIBXXF86VM )
set(CONAN_RES_DIRS_LIBXXF86VM )
set(CONAN_SRC_DIRS_LIBXXF86VM )
set(CONAN_BUILD_DIRS_LIBXXF86VM "/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/"
			"/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXXF86VM )
set(CONAN_LIBS_LIBXXF86VM Xxf86vm)
set(CONAN_PKG_LIBS_LIBXXF86VM Xxf86vm)
set(CONAN_SYSTEM_LIBS_LIBXXF86VM )
set(CONAN_FRAMEWORKS_LIBXXF86VM )
set(CONAN_FRAMEWORKS_FOUND_LIBXXF86VM "")  # Will be filled later
set(CONAN_DEFINES_LIBXXF86VM )
set(CONAN_BUILD_MODULES_PATHS_LIBXXF86VM )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXXF86VM )

set(CONAN_C_FLAGS_LIBXXF86VM "")
set(CONAN_CXX_FLAGS_LIBXXF86VM "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXXF86VM "")
set(CONAN_EXE_LINKER_FLAGS_LIBXXF86VM "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXXF86VM_LIST "")
set(CONAN_CXX_FLAGS_LIBXXF86VM_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXXF86VM_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXXF86VM_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXXF86VM "${CONAN_FRAMEWORKS_LIBXXF86VM}" "_LIBXXF86VM")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXXF86VM ${CONAN_PKG_LIBS_LIBXXF86VM} ${CONAN_SYSTEM_LIBS_LIBXXF86VM} ${CONAN_FRAMEWORKS_FOUND_LIBXXF86VM})


#################
###  LIBXRENDER
#################
set(CONAN_LIBXRENDER_ROOT "/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967")
set(CONAN_INCLUDE_DIRS_LIBXRENDER "/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/include")
set(CONAN_LIB_DIRS_LIBXRENDER "/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib")
set(CONAN_BIN_DIRS_LIBXRENDER )
set(CONAN_RES_DIRS_LIBXRENDER )
set(CONAN_SRC_DIRS_LIBXRENDER )
set(CONAN_BUILD_DIRS_LIBXRENDER "/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/"
			"/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXRENDER )
set(CONAN_LIBS_LIBXRENDER Xrender)
set(CONAN_PKG_LIBS_LIBXRENDER Xrender)
set(CONAN_SYSTEM_LIBS_LIBXRENDER )
set(CONAN_FRAMEWORKS_LIBXRENDER )
set(CONAN_FRAMEWORKS_FOUND_LIBXRENDER "")  # Will be filled later
set(CONAN_DEFINES_LIBXRENDER )
set(CONAN_BUILD_MODULES_PATHS_LIBXRENDER )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXRENDER )

set(CONAN_C_FLAGS_LIBXRENDER "")
set(CONAN_CXX_FLAGS_LIBXRENDER "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXRENDER "")
set(CONAN_EXE_LINKER_FLAGS_LIBXRENDER "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXRENDER_LIST "")
set(CONAN_CXX_FLAGS_LIBXRENDER_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXRENDER_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXRENDER_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXRENDER "${CONAN_FRAMEWORKS_LIBXRENDER}" "_LIBXRENDER")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXRENDER ${CONAN_PKG_LIBS_LIBXRENDER} ${CONAN_SYSTEM_LIBS_LIBXRENDER} ${CONAN_FRAMEWORKS_FOUND_LIBXRENDER})


#################
###  LIBXEXT
#################
set(CONAN_LIBXEXT_ROOT "/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967")
set(CONAN_INCLUDE_DIRS_LIBXEXT "/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/include")
set(CONAN_LIB_DIRS_LIBXEXT "/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib")
set(CONAN_BIN_DIRS_LIBXEXT )
set(CONAN_RES_DIRS_LIBXEXT )
set(CONAN_SRC_DIRS_LIBXEXT )
set(CONAN_BUILD_DIRS_LIBXEXT "/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/"
			"/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXEXT )
set(CONAN_LIBS_LIBXEXT Xext)
set(CONAN_PKG_LIBS_LIBXEXT Xext)
set(CONAN_SYSTEM_LIBS_LIBXEXT dl)
set(CONAN_FRAMEWORKS_LIBXEXT )
set(CONAN_FRAMEWORKS_FOUND_LIBXEXT "")  # Will be filled later
set(CONAN_DEFINES_LIBXEXT )
set(CONAN_BUILD_MODULES_PATHS_LIBXEXT )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXEXT )

set(CONAN_C_FLAGS_LIBXEXT "")
set(CONAN_CXX_FLAGS_LIBXEXT "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXEXT "")
set(CONAN_EXE_LINKER_FLAGS_LIBXEXT "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXEXT_LIST "")
set(CONAN_CXX_FLAGS_LIBXEXT_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXEXT_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXEXT_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXEXT "${CONAN_FRAMEWORKS_LIBXEXT}" "_LIBXEXT")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXEXT ${CONAN_PKG_LIBS_LIBXEXT} ${CONAN_SYSTEM_LIBS_LIBXEXT} ${CONAN_FRAMEWORKS_FOUND_LIBXEXT})


#################
###  LIBXFIXES
#################
set(CONAN_LIBXFIXES_ROOT "/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967")
set(CONAN_INCLUDE_DIRS_LIBXFIXES "/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/include")
set(CONAN_LIB_DIRS_LIBXFIXES "/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib")
set(CONAN_BIN_DIRS_LIBXFIXES )
set(CONAN_RES_DIRS_LIBXFIXES )
set(CONAN_SRC_DIRS_LIBXFIXES )
set(CONAN_BUILD_DIRS_LIBXFIXES "/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/"
			"/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXFIXES )
set(CONAN_LIBS_LIBXFIXES Xfixes)
set(CONAN_PKG_LIBS_LIBXFIXES Xfixes)
set(CONAN_SYSTEM_LIBS_LIBXFIXES )
set(CONAN_FRAMEWORKS_LIBXFIXES )
set(CONAN_FRAMEWORKS_FOUND_LIBXFIXES "")  # Will be filled later
set(CONAN_DEFINES_LIBXFIXES )
set(CONAN_BUILD_MODULES_PATHS_LIBXFIXES )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXFIXES )

set(CONAN_C_FLAGS_LIBXFIXES "")
set(CONAN_CXX_FLAGS_LIBXFIXES "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXFIXES "")
set(CONAN_EXE_LINKER_FLAGS_LIBXFIXES "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXFIXES_LIST "")
set(CONAN_CXX_FLAGS_LIBXFIXES_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXFIXES_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXFIXES_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXFIXES "${CONAN_FRAMEWORKS_LIBXFIXES}" "_LIBXFIXES")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXFIXES ${CONAN_PKG_LIBS_LIBXFIXES} ${CONAN_SYSTEM_LIBS_LIBXFIXES} ${CONAN_FRAMEWORKS_FOUND_LIBXFIXES})


#################
###  LIBPCIACCESS
#################
set(CONAN_LIBPCIACCESS_ROOT "/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8")
set(CONAN_INCLUDE_DIRS_LIBPCIACCESS "/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include")
set(CONAN_LIB_DIRS_LIBPCIACCESS "/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib")
set(CONAN_BIN_DIRS_LIBPCIACCESS )
set(CONAN_RES_DIRS_LIBPCIACCESS )
set(CONAN_SRC_DIRS_LIBPCIACCESS )
set(CONAN_BUILD_DIRS_LIBPCIACCESS "/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/"
			"/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBPCIACCESS )
set(CONAN_LIBS_LIBPCIACCESS pciaccess)
set(CONAN_PKG_LIBS_LIBPCIACCESS pciaccess)
set(CONAN_SYSTEM_LIBS_LIBPCIACCESS )
set(CONAN_FRAMEWORKS_LIBPCIACCESS )
set(CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS "")  # Will be filled later
set(CONAN_DEFINES_LIBPCIACCESS )
set(CONAN_BUILD_MODULES_PATHS_LIBPCIACCESS )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBPCIACCESS )

set(CONAN_C_FLAGS_LIBPCIACCESS "")
set(CONAN_CXX_FLAGS_LIBPCIACCESS "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPCIACCESS "")
set(CONAN_EXE_LINKER_FLAGS_LIBPCIACCESS "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBPCIACCESS_LIST "")
set(CONAN_CXX_FLAGS_LIBPCIACCESS_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPCIACCESS_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBPCIACCESS_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS "${CONAN_FRAMEWORKS_LIBPCIACCESS}" "_LIBPCIACCESS")
# Append to aggregated values variable
set(CONAN_LIBS_LIBPCIACCESS ${CONAN_PKG_LIBS_LIBPCIACCESS} ${CONAN_SYSTEM_LIBS_LIBPCIACCESS} ${CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS})


#################
###  XZ_UTILS
#################
set(CONAN_XZ_UTILS_ROOT "/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8")
set(CONAN_INCLUDE_DIRS_XZ_UTILS "/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include")
set(CONAN_LIB_DIRS_XZ_UTILS "/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib")
set(CONAN_BIN_DIRS_XZ_UTILS "/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/bin")
set(CONAN_RES_DIRS_XZ_UTILS )
set(CONAN_SRC_DIRS_XZ_UTILS )
set(CONAN_BUILD_DIRS_XZ_UTILS "/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/")
set(CONAN_FRAMEWORK_DIRS_XZ_UTILS )
set(CONAN_LIBS_XZ_UTILS lzma)
set(CONAN_PKG_LIBS_XZ_UTILS lzma)
set(CONAN_SYSTEM_LIBS_XZ_UTILS )
set(CONAN_FRAMEWORKS_XZ_UTILS )
set(CONAN_FRAMEWORKS_FOUND_XZ_UTILS "")  # Will be filled later
set(CONAN_DEFINES_XZ_UTILS "-DLZMA_API_STATIC")
set(CONAN_BUILD_MODULES_PATHS_XZ_UTILS )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_XZ_UTILS "LZMA_API_STATIC")

set(CONAN_C_FLAGS_XZ_UTILS "")
set(CONAN_CXX_FLAGS_XZ_UTILS "")
set(CONAN_SHARED_LINKER_FLAGS_XZ_UTILS "")
set(CONAN_EXE_LINKER_FLAGS_XZ_UTILS "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_XZ_UTILS_LIST "")
set(CONAN_CXX_FLAGS_XZ_UTILS_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_LIST "")
set(CONAN_EXE_LINKER_FLAGS_XZ_UTILS_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_XZ_UTILS "${CONAN_FRAMEWORKS_XZ_UTILS}" "_XZ_UTILS")
# Append to aggregated values variable
set(CONAN_LIBS_XZ_UTILS ${CONAN_PKG_LIBS_XZ_UTILS} ${CONAN_SYSTEM_LIBS_XZ_UTILS} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS})


#################
###  LIBX11
#################
set(CONAN_LIBX11_ROOT "/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783")
set(CONAN_INCLUDE_DIRS_LIBX11 "/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/include")
set(CONAN_LIB_DIRS_LIBX11 "/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/lib")
set(CONAN_BIN_DIRS_LIBX11 )
set(CONAN_RES_DIRS_LIBX11 )
set(CONAN_SRC_DIRS_LIBX11 )
set(CONAN_BUILD_DIRS_LIBX11 "/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/"
			"/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBX11 )
set(CONAN_LIBS_LIBX11 X11)
set(CONAN_PKG_LIBS_LIBX11 X11)
set(CONAN_SYSTEM_LIBS_LIBX11 dl)
set(CONAN_FRAMEWORKS_LIBX11 )
set(CONAN_FRAMEWORKS_FOUND_LIBX11 "")  # Will be filled later
set(CONAN_DEFINES_LIBX11 )
set(CONAN_BUILD_MODULES_PATHS_LIBX11 )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBX11 )

set(CONAN_C_FLAGS_LIBX11 "")
set(CONAN_CXX_FLAGS_LIBX11 "")
set(CONAN_SHARED_LINKER_FLAGS_LIBX11 "")
set(CONAN_EXE_LINKER_FLAGS_LIBX11 "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBX11_LIST "")
set(CONAN_CXX_FLAGS_LIBX11_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBX11_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBX11_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBX11 "${CONAN_FRAMEWORKS_LIBX11}" "_LIBX11")
# Append to aggregated values variable
set(CONAN_LIBS_LIBX11 ${CONAN_PKG_LIBS_LIBX11} ${CONAN_SYSTEM_LIBS_LIBX11} ${CONAN_FRAMEWORKS_FOUND_LIBX11})


#################
###  XTRANS
#################
set(CONAN_XTRANS_ROOT "/home/user/.conan/data/xtrans/1.4.0/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9")
set(CONAN_INCLUDE_DIRS_XTRANS "/home/user/.conan/data/xtrans/1.4.0/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include")
set(CONAN_LIB_DIRS_XTRANS )
set(CONAN_BIN_DIRS_XTRANS )
set(CONAN_RES_DIRS_XTRANS )
set(CONAN_SRC_DIRS_XTRANS )
set(CONAN_BUILD_DIRS_XTRANS "/home/user/.conan/data/xtrans/1.4.0/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xtrans/1.4.0/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/share/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_XTRANS )
set(CONAN_LIBS_XTRANS )
set(CONAN_PKG_LIBS_XTRANS )
set(CONAN_SYSTEM_LIBS_XTRANS )
set(CONAN_FRAMEWORKS_XTRANS )
set(CONAN_FRAMEWORKS_FOUND_XTRANS "")  # Will be filled later
set(CONAN_DEFINES_XTRANS )
set(CONAN_BUILD_MODULES_PATHS_XTRANS )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_XTRANS )

set(CONAN_C_FLAGS_XTRANS "")
set(CONAN_CXX_FLAGS_XTRANS "")
set(CONAN_SHARED_LINKER_FLAGS_XTRANS "")
set(CONAN_EXE_LINKER_FLAGS_XTRANS "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_XTRANS_LIST "")
set(CONAN_CXX_FLAGS_XTRANS_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_XTRANS_LIST "")
set(CONAN_EXE_LINKER_FLAGS_XTRANS_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_XTRANS "${CONAN_FRAMEWORKS_XTRANS}" "_XTRANS")
# Append to aggregated values variable
set(CONAN_LIBS_XTRANS ${CONAN_PKG_LIBS_XTRANS} ${CONAN_SYSTEM_LIBS_XTRANS} ${CONAN_FRAMEWORKS_FOUND_XTRANS})


#################
###  LIBXCB
#################
set(CONAN_LIBXCB_ROOT "/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f")
set(CONAN_INCLUDE_DIRS_LIBXCB "/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/include")
set(CONAN_LIB_DIRS_LIBXCB "/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/lib")
set(CONAN_BIN_DIRS_LIBXCB )
set(CONAN_RES_DIRS_LIBXCB )
set(CONAN_SRC_DIRS_LIBXCB )
set(CONAN_BUILD_DIRS_LIBXCB "/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/"
			"/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXCB )
set(CONAN_LIBS_LIBXCB xcb)
set(CONAN_PKG_LIBS_LIBXCB xcb)
set(CONAN_SYSTEM_LIBS_LIBXCB )
set(CONAN_FRAMEWORKS_LIBXCB )
set(CONAN_FRAMEWORKS_FOUND_LIBXCB "")  # Will be filled later
set(CONAN_DEFINES_LIBXCB )
set(CONAN_BUILD_MODULES_PATHS_LIBXCB )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXCB )

set(CONAN_C_FLAGS_LIBXCB "")
set(CONAN_CXX_FLAGS_LIBXCB "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXCB "")
set(CONAN_EXE_LINKER_FLAGS_LIBXCB "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXCB_LIST "")
set(CONAN_CXX_FLAGS_LIBXCB_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXCB_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXCB_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXCB "${CONAN_FRAMEWORKS_LIBXCB}" "_LIBXCB")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXCB ${CONAN_PKG_LIBS_LIBXCB} ${CONAN_SYSTEM_LIBS_LIBXCB} ${CONAN_FRAMEWORKS_FOUND_LIBXCB})


#################
###  XCB-PROTO
#################
set(CONAN_XCB-PROTO_ROOT "/home/user/.conan/data/xcb-proto/1.13/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9")
set(CONAN_INCLUDE_DIRS_XCB-PROTO )
set(CONAN_LIB_DIRS_XCB-PROTO "/home/user/.conan/data/xcb-proto/1.13/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib")
set(CONAN_BIN_DIRS_XCB-PROTO )
set(CONAN_RES_DIRS_XCB-PROTO )
set(CONAN_SRC_DIRS_XCB-PROTO )
set(CONAN_BUILD_DIRS_XCB-PROTO "/home/user/.conan/data/xcb-proto/1.13/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xcb-proto/1.13/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_XCB-PROTO )
set(CONAN_LIBS_XCB-PROTO )
set(CONAN_PKG_LIBS_XCB-PROTO )
set(CONAN_SYSTEM_LIBS_XCB-PROTO )
set(CONAN_FRAMEWORKS_XCB-PROTO )
set(CONAN_FRAMEWORKS_FOUND_XCB-PROTO "")  # Will be filled later
set(CONAN_DEFINES_XCB-PROTO )
set(CONAN_BUILD_MODULES_PATHS_XCB-PROTO )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_XCB-PROTO )

set(CONAN_C_FLAGS_XCB-PROTO "")
set(CONAN_CXX_FLAGS_XCB-PROTO "")
set(CONAN_SHARED_LINKER_FLAGS_XCB-PROTO "")
set(CONAN_EXE_LINKER_FLAGS_XCB-PROTO "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_XCB-PROTO_LIST "")
set(CONAN_CXX_FLAGS_XCB-PROTO_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_XCB-PROTO_LIST "")
set(CONAN_EXE_LINKER_FLAGS_XCB-PROTO_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_XCB-PROTO "${CONAN_FRAMEWORKS_XCB-PROTO}" "_XCB-PROTO")
# Append to aggregated values variable
set(CONAN_LIBS_XCB-PROTO ${CONAN_PKG_LIBS_XCB-PROTO} ${CONAN_SYSTEM_LIBS_XCB-PROTO} ${CONAN_FRAMEWORKS_FOUND_XCB-PROTO})


#################
###  UTIL-MACROS
#################
set(CONAN_UTIL-MACROS_ROOT "/home/user/.conan/data/util-macros/1.19.2/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9")
set(CONAN_INCLUDE_DIRS_UTIL-MACROS )
set(CONAN_LIB_DIRS_UTIL-MACROS )
set(CONAN_BIN_DIRS_UTIL-MACROS )
set(CONAN_RES_DIRS_UTIL-MACROS )
set(CONAN_SRC_DIRS_UTIL-MACROS )
set(CONAN_BUILD_DIRS_UTIL-MACROS "/home/user/.conan/data/util-macros/1.19.2/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/util-macros/1.19.2/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/share/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_UTIL-MACROS )
set(CONAN_LIBS_UTIL-MACROS )
set(CONAN_PKG_LIBS_UTIL-MACROS )
set(CONAN_SYSTEM_LIBS_UTIL-MACROS )
set(CONAN_FRAMEWORKS_UTIL-MACROS )
set(CONAN_FRAMEWORKS_FOUND_UTIL-MACROS "")  # Will be filled later
set(CONAN_DEFINES_UTIL-MACROS )
set(CONAN_BUILD_MODULES_PATHS_UTIL-MACROS )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_UTIL-MACROS )

set(CONAN_C_FLAGS_UTIL-MACROS "")
set(CONAN_CXX_FLAGS_UTIL-MACROS "")
set(CONAN_SHARED_LINKER_FLAGS_UTIL-MACROS "")
set(CONAN_EXE_LINKER_FLAGS_UTIL-MACROS "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_UTIL-MACROS_LIST "")
set(CONAN_CXX_FLAGS_UTIL-MACROS_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_UTIL-MACROS_LIST "")
set(CONAN_EXE_LINKER_FLAGS_UTIL-MACROS_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_UTIL-MACROS "${CONAN_FRAMEWORKS_UTIL-MACROS}" "_UTIL-MACROS")
# Append to aggregated values variable
set(CONAN_LIBS_UTIL-MACROS ${CONAN_PKG_LIBS_UTIL-MACROS} ${CONAN_SYSTEM_LIBS_UTIL-MACROS} ${CONAN_FRAMEWORKS_FOUND_UTIL-MACROS})


#################
###  LIBXAU
#################
set(CONAN_LIBXAU_ROOT "/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab")
set(CONAN_INCLUDE_DIRS_LIBXAU "/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/include")
set(CONAN_LIB_DIRS_LIBXAU "/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/lib")
set(CONAN_BIN_DIRS_LIBXAU )
set(CONAN_RES_DIRS_LIBXAU )
set(CONAN_SRC_DIRS_LIBXAU )
set(CONAN_BUILD_DIRS_LIBXAU "/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/"
			"/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXAU )
set(CONAN_LIBS_LIBXAU Xau)
set(CONAN_PKG_LIBS_LIBXAU Xau)
set(CONAN_SYSTEM_LIBS_LIBXAU )
set(CONAN_FRAMEWORKS_LIBXAU )
set(CONAN_FRAMEWORKS_FOUND_LIBXAU "")  # Will be filled later
set(CONAN_DEFINES_LIBXAU )
set(CONAN_BUILD_MODULES_PATHS_LIBXAU )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXAU )

set(CONAN_C_FLAGS_LIBXAU "")
set(CONAN_CXX_FLAGS_LIBXAU "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXAU "")
set(CONAN_EXE_LINKER_FLAGS_LIBXAU "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXAU_LIST "")
set(CONAN_CXX_FLAGS_LIBXAU_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXAU_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXAU_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXAU "${CONAN_FRAMEWORKS_LIBXAU}" "_LIBXAU")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXAU ${CONAN_PKG_LIBS_LIBXAU} ${CONAN_SYSTEM_LIBS_LIBXAU} ${CONAN_FRAMEWORKS_FOUND_LIBXAU})


#################
###  LIBPTHREAD-STUBS
#################
set(CONAN_LIBPTHREAD-STUBS_ROOT "/home/user/.conan/data/libpthread-stubs/0.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9")
set(CONAN_INCLUDE_DIRS_LIBPTHREAD-STUBS )
set(CONAN_LIB_DIRS_LIBPTHREAD-STUBS "/home/user/.conan/data/libpthread-stubs/0.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib")
set(CONAN_BIN_DIRS_LIBPTHREAD-STUBS )
set(CONAN_RES_DIRS_LIBPTHREAD-STUBS )
set(CONAN_SRC_DIRS_LIBPTHREAD-STUBS )
set(CONAN_BUILD_DIRS_LIBPTHREAD-STUBS "/home/user/.conan/data/libpthread-stubs/0.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/libpthread-stubs/0.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBPTHREAD-STUBS )
set(CONAN_LIBS_LIBPTHREAD-STUBS )
set(CONAN_PKG_LIBS_LIBPTHREAD-STUBS )
set(CONAN_SYSTEM_LIBS_LIBPTHREAD-STUBS )
set(CONAN_FRAMEWORKS_LIBPTHREAD-STUBS )
set(CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS "")  # Will be filled later
set(CONAN_DEFINES_LIBPTHREAD-STUBS )
set(CONAN_BUILD_MODULES_PATHS_LIBPTHREAD-STUBS )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBPTHREAD-STUBS )

set(CONAN_C_FLAGS_LIBPTHREAD-STUBS "")
set(CONAN_CXX_FLAGS_LIBPTHREAD-STUBS "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPTHREAD-STUBS "")
set(CONAN_EXE_LINKER_FLAGS_LIBPTHREAD-STUBS "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBPTHREAD-STUBS_LIST "")
set(CONAN_CXX_FLAGS_LIBPTHREAD-STUBS_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPTHREAD-STUBS_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBPTHREAD-STUBS_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS "${CONAN_FRAMEWORKS_LIBPTHREAD-STUBS}" "_LIBPTHREAD-STUBS")
# Append to aggregated values variable
set(CONAN_LIBS_LIBPTHREAD-STUBS ${CONAN_PKG_LIBS_LIBPTHREAD-STUBS} ${CONAN_SYSTEM_LIBS_LIBPTHREAD-STUBS} ${CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS})


#################
###  LIBXDMCP
#################
set(CONAN_LIBXDMCP_ROOT "/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72")
set(CONAN_INCLUDE_DIRS_LIBXDMCP "/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/include")
set(CONAN_LIB_DIRS_LIBXDMCP "/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/lib")
set(CONAN_BIN_DIRS_LIBXDMCP )
set(CONAN_RES_DIRS_LIBXDMCP )
set(CONAN_SRC_DIRS_LIBXDMCP )
set(CONAN_BUILD_DIRS_LIBXDMCP "/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/"
			"/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_LIBXDMCP )
set(CONAN_LIBS_LIBXDMCP Xdmcp)
set(CONAN_PKG_LIBS_LIBXDMCP Xdmcp)
set(CONAN_SYSTEM_LIBS_LIBXDMCP )
set(CONAN_FRAMEWORKS_LIBXDMCP )
set(CONAN_FRAMEWORKS_FOUND_LIBXDMCP "")  # Will be filled later
set(CONAN_DEFINES_LIBXDMCP )
set(CONAN_BUILD_MODULES_PATHS_LIBXDMCP )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBXDMCP )

set(CONAN_C_FLAGS_LIBXDMCP "")
set(CONAN_CXX_FLAGS_LIBXDMCP "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXDMCP "")
set(CONAN_EXE_LINKER_FLAGS_LIBXDMCP "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBXDMCP_LIST "")
set(CONAN_CXX_FLAGS_LIBXDMCP_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBXDMCP_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBXDMCP_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBXDMCP "${CONAN_FRAMEWORKS_LIBXDMCP}" "_LIBXDMCP")
# Append to aggregated values variable
set(CONAN_LIBS_LIBXDMCP ${CONAN_PKG_LIBS_LIBXDMCP} ${CONAN_SYSTEM_LIBS_LIBXDMCP} ${CONAN_FRAMEWORKS_FOUND_LIBXDMCP})


#################
###  XORGPROTO
#################
set(CONAN_XORGPROTO_ROOT "/home/user/.conan/data/xorgproto/2019.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9")
set(CONAN_INCLUDE_DIRS_XORGPROTO "/home/user/.conan/data/xorgproto/2019.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include")
set(CONAN_LIB_DIRS_XORGPROTO )
set(CONAN_BIN_DIRS_XORGPROTO )
set(CONAN_RES_DIRS_XORGPROTO )
set(CONAN_SRC_DIRS_XORGPROTO )
set(CONAN_BUILD_DIRS_XORGPROTO "/home/user/.conan/data/xorgproto/2019.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xorgproto/2019.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/share/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_XORGPROTO )
set(CONAN_LIBS_XORGPROTO )
set(CONAN_PKG_LIBS_XORGPROTO )
set(CONAN_SYSTEM_LIBS_XORGPROTO )
set(CONAN_FRAMEWORKS_XORGPROTO )
set(CONAN_FRAMEWORKS_FOUND_XORGPROTO "")  # Will be filled later
set(CONAN_DEFINES_XORGPROTO )
set(CONAN_BUILD_MODULES_PATHS_XORGPROTO )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_XORGPROTO )

set(CONAN_C_FLAGS_XORGPROTO "")
set(CONAN_CXX_FLAGS_XORGPROTO "")
set(CONAN_SHARED_LINKER_FLAGS_XORGPROTO "")
set(CONAN_EXE_LINKER_FLAGS_XORGPROTO "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_XORGPROTO_LIST "")
set(CONAN_CXX_FLAGS_XORGPROTO_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_XORGPROTO_LIST "")
set(CONAN_EXE_LINKER_FLAGS_XORGPROTO_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_XORGPROTO "${CONAN_FRAMEWORKS_XORGPROTO}" "_XORGPROTO")
# Append to aggregated values variable
set(CONAN_LIBS_XORGPROTO ${CONAN_PKG_LIBS_XORGPROTO} ${CONAN_SYSTEM_LIBS_XORGPROTO} ${CONAN_FRAMEWORKS_FOUND_XORGPROTO})


#################
###  XPROTO
#################
set(CONAN_XPROTO_ROOT "/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9")
set(CONAN_INCLUDE_DIRS_XPROTO "/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include")
set(CONAN_LIB_DIRS_XPROTO "/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib")
set(CONAN_BIN_DIRS_XPROTO )
set(CONAN_RES_DIRS_XPROTO )
set(CONAN_SRC_DIRS_XPROTO )
set(CONAN_BUILD_DIRS_XPROTO "/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib/pkgconfig")
set(CONAN_FRAMEWORK_DIRS_XPROTO )
set(CONAN_LIBS_XPROTO )
set(CONAN_PKG_LIBS_XPROTO )
set(CONAN_SYSTEM_LIBS_XPROTO )
set(CONAN_FRAMEWORKS_XPROTO )
set(CONAN_FRAMEWORKS_FOUND_XPROTO "")  # Will be filled later
set(CONAN_DEFINES_XPROTO )
set(CONAN_BUILD_MODULES_PATHS_XPROTO )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_XPROTO )

set(CONAN_C_FLAGS_XPROTO "")
set(CONAN_CXX_FLAGS_XPROTO "")
set(CONAN_SHARED_LINKER_FLAGS_XPROTO "")
set(CONAN_EXE_LINKER_FLAGS_XPROTO "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_XPROTO_LIST "")
set(CONAN_CXX_FLAGS_XPROTO_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_XPROTO_LIST "")
set(CONAN_EXE_LINKER_FLAGS_XPROTO_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_XPROTO "${CONAN_FRAMEWORKS_XPROTO}" "_XPROTO")
# Append to aggregated values variable
set(CONAN_LIBS_XPROTO ${CONAN_PKG_LIBS_XPROTO} ${CONAN_SYSTEM_LIBS_XPROTO} ${CONAN_FRAMEWORKS_FOUND_XPROTO})


### Definition of global aggregated variables ###

set(CONAN_PACKAGE_NAME None)
set(CONAN_PACKAGE_VERSION None)

set(CONAN_SETTINGS_ARCH "x86_64")
set(CONAN_SETTINGS_ARCH_BUILD "x86_64")
set(CONAN_SETTINGS_BUILD_TYPE "Debug")
set(CONAN_SETTINGS_COMPILER "gcc")
set(CONAN_SETTINGS_COMPILER_LIBCXX "libstdc++11")
set(CONAN_SETTINGS_COMPILER_VERSION "9")
set(CONAN_SETTINGS_OS "Linux")
set(CONAN_SETTINGS_OS_BUILD "Linux")

set(CONAN_DEPENDENCIES glfw libxinerama libxcursor libxi mesa libxrandr zlib expat libdrm libelf libunwind libxdamage libxshmfence libxxf86vm libxrender libxext libxfixes libpciaccess xz_utils libx11 xtrans libxcb xcb-proto util-macros libxau libpthread-stubs libxdmcp xorgproto xproto)
# Storing original command line args (CMake helper) flags
set(CONAN_CMD_CXX_FLAGS ${CONAN_CXX_FLAGS})

set(CONAN_CMD_SHARED_LINKER_FLAGS ${CONAN_SHARED_LINKER_FLAGS})
set(CONAN_CMD_C_FLAGS ${CONAN_C_FLAGS})
# Defining accumulated conan variables for all deps

set(CONAN_INCLUDE_DIRS "/home/user/.conan/data/glfw/3.3.2/bincrafters/stable/package/6a0b195b06ef5fbc1ca4422976fe500aeb5bab2c/include"
			"/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/include"
			"/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/include"
			"/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/include"
			"/home/user/.conan/data/mesa/19.3.1/bincrafters/stable/package/4738ebe557ba170d04ecce21fcb989f0bce5f442/include"
			"/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/include"
			"/home/user/.conan/data/zlib/1.2.11/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include"
			"/home/user/.conan/data/expat/2.2.9/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include"
			"/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/include"
			"/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/include/libdrm"
			"/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/include/libkms"
			"/home/user/.conan/data/libelf/0.8.13/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include"
			"/home/user/.conan/data/libunwind/1.3.1/_/_/package/eef58b252f2cfddca30f2e8758005c7d67542d8a/include"
			"/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/include"
			"/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/include"
			"/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/include"
			"/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/include"
			"/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/include"
			"/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/include"
			"/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include"
			"/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/include"
			"/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/include"
			"/home/user/.conan/data/xtrans/1.4.0/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include"
			"/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/include"
			"/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/include"
			"/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/include"
			"/home/user/.conan/data/xorgproto/2019.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include"
			"/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include" ${CONAN_INCLUDE_DIRS})
set(CONAN_LIB_DIRS "/home/user/.conan/data/glfw/3.3.2/bincrafters/stable/package/6a0b195b06ef5fbc1ca4422976fe500aeb5bab2c/lib"
			"/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib"
			"/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/lib"
			"/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib"
			"/home/user/.conan/data/mesa/19.3.1/bincrafters/stable/package/4738ebe557ba170d04ecce21fcb989f0bce5f442/lib"
			"/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/lib"
			"/home/user/.conan/data/zlib/1.2.11/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib"
			"/home/user/.conan/data/expat/2.2.9/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib"
			"/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/lib"
			"/home/user/.conan/data/libelf/0.8.13/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib"
			"/home/user/.conan/data/libunwind/1.3.1/_/_/package/eef58b252f2cfddca30f2e8758005c7d67542d8a/lib"
			"/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/lib"
			"/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/lib"
			"/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/lib"
			"/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib"
			"/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib"
			"/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib"
			"/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib"
			"/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib"
			"/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/lib"
			"/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/lib"
			"/home/user/.conan/data/xcb-proto/1.13/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib"
			"/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/lib"
			"/home/user/.conan/data/libpthread-stubs/0.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib"
			"/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/lib"
			"/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib" ${CONAN_LIB_DIRS})
set(CONAN_BIN_DIRS "/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/bin" ${CONAN_BIN_DIRS})
set(CONAN_RES_DIRS  ${CONAN_RES_DIRS})
set(CONAN_FRAMEWORK_DIRS  ${CONAN_FRAMEWORK_DIRS})
set(CONAN_LIBS glfw3 Xinerama Xcursor Xi EGL GL gbm glapi vulkan_intel Xrandr z expat drm drm_amdgpu drm_freedreno drm_intel drm_nouveau drm_radeon kms elf unwind unwind-coredump unwind-generic unwind-ptrace unwind-setjmp unwind-x86_64 Xdamage xshmfence Xxf86vm Xrender Xext Xfixes pciaccess lzma X11 xcb Xau Xdmcp ${CONAN_LIBS})
set(CONAN_PKG_LIBS glfw3 Xinerama Xcursor Xi EGL GL gbm glapi vulkan_intel Xrandr z expat drm drm_amdgpu drm_freedreno drm_intel drm_nouveau drm_radeon kms elf unwind unwind-coredump unwind-generic unwind-ptrace unwind-setjmp unwind-x86_64 Xdamage xshmfence Xxf86vm Xrender Xext Xfixes pciaccess lzma X11 xcb Xau Xdmcp ${CONAN_PKG_LIBS})
set(CONAN_SYSTEM_LIBS m pthread dl ${CONAN_SYSTEM_LIBS})
set(CONAN_FRAMEWORKS  ${CONAN_FRAMEWORKS})
set(CONAN_FRAMEWORKS_FOUND "")  # Will be filled later
set(CONAN_DEFINES "-DLZMA_API_STATIC"
			"-DXML_STATIC" ${CONAN_DEFINES})
set(CONAN_BUILD_MODULES_PATHS  ${CONAN_BUILD_MODULES_PATHS})
set(CONAN_CMAKE_MODULE_PATH "/home/user/.conan/data/glfw/3.3.2/bincrafters/stable/package/6a0b195b06ef5fbc1ca4422976fe500aeb5bab2c/"
			"/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/"
			"/home/user/.conan/data/libxinerama/1.1.4/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib/pkgconfig"
			"/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/"
			"/home/user/.conan/data/libxcursor/1.2.0/bincrafters/stable/package/dac6d457f8e28d09d9c6c27a83eb2b6b5aff3fc7/lib/pkgconfig"
			"/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/"
			"/home/user/.conan/data/libxi/1.7.10/bincrafters/stable/package/24899c9c48c7638e3ffc80c34aaa9ea07b516d56/lib/pkgconfig"
			"/home/user/.conan/data/mesa/19.3.1/bincrafters/stable/package/4738ebe557ba170d04ecce21fcb989f0bce5f442/"
			"/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/"
			"/home/user/.conan/data/libxrandr/1.5.2/bincrafters/stable/package/3ed31e8e448b5f476748003b2cb8087256acc7e3/lib/pkgconfig"
			"/home/user/.conan/data/zlib/1.2.11/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/"
			"/home/user/.conan/data/expat/2.2.9/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/"
			"/home/user/.conan/data/libdrm/2.4.100/bincrafters/stable/package/2c29f667cacc7eeb03f56d878f99f7ce8b3d6168/"
			"/home/user/.conan/data/libelf/0.8.13/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/"
			"/home/user/.conan/data/libunwind/1.3.1/_/_/package/eef58b252f2cfddca30f2e8758005c7d67542d8a/"
			"/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/"
			"/home/user/.conan/data/libxdamage/1.1.5/bincrafters/stable/package/c1d5e051bbd1076350f63a36fe423230726ed6a6/lib/pkgconfig"
			"/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/"
			"/home/user/.conan/data/libxshmfence/1.3/bincrafters/stable/package/98bc0352e079a667d0edbedb786305b0971aa660/lib/pkgconfig"
			"/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/"
			"/home/user/.conan/data/libxxf86vm/1.1.4/bincrafters/stable/package/b305f54ba4e27810ceb49cac130bdec766fea836/lib/pkgconfig"
			"/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/"
			"/home/user/.conan/data/libxrender/0.9.10/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib/pkgconfig"
			"/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/"
			"/home/user/.conan/data/libxext/1.3.4/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib/pkgconfig"
			"/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/"
			"/home/user/.conan/data/libxfixes/5.0.3/bincrafters/stable/package/3094f02cc92d072ef64199f75ca7e0f3a45fa967/lib/pkgconfig"
			"/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/"
			"/home/user/.conan/data/libpciaccess/0.16/bincrafters/stable/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/lib/pkgconfig"
			"/home/user/.conan/data/xz_utils/5.2.4/_/_/package/23b828d52c0630e6b0b96d2945419feb7843c4f8/"
			"/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/"
			"/home/user/.conan/data/libx11/1.6.8/bincrafters/stable/package/fb4de4452309896753239ba8144a4acb9d0f0783/lib/pkgconfig"
			"/home/user/.conan/data/xtrans/1.4.0/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xtrans/1.4.0/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/share/pkgconfig"
			"/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/"
			"/home/user/.conan/data/libxcb/1.13.1/bincrafters/stable/package/b8c98b327e58b392e50971217071e1166220829f/lib/pkgconfig"
			"/home/user/.conan/data/xcb-proto/1.13/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xcb-proto/1.13/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib/pkgconfig"
			"/home/user/.conan/data/util-macros/1.19.2/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/util-macros/1.19.2/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/share/pkgconfig"
			"/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/"
			"/home/user/.conan/data/libxau/1.0.9/bincrafters/stable/package/c99c7836a95e8848c6575783d12ace1982abacab/lib/pkgconfig"
			"/home/user/.conan/data/libpthread-stubs/0.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/libpthread-stubs/0.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib/pkgconfig"
			"/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/"
			"/home/user/.conan/data/libxdmcp/1.1.3/bincrafters/stable/package/27635b69fcb5b0b49e17a4c6b12ffba465651c72/lib/pkgconfig"
			"/home/user/.conan/data/xorgproto/2019.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xorgproto/2019.1/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/share/pkgconfig"
			"/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/"
			"/home/user/.conan/data/xproto/7.0.31/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/lib/pkgconfig" ${CONAN_CMAKE_MODULE_PATH})

set(CONAN_CXX_FLAGS " ${CONAN_CXX_FLAGS}")
set(CONAN_SHARED_LINKER_FLAGS " ${CONAN_SHARED_LINKER_FLAGS}")
set(CONAN_EXE_LINKER_FLAGS " ${CONAN_EXE_LINKER_FLAGS}")
set(CONAN_C_FLAGS " ${CONAN_C_FLAGS}")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND "${CONAN_FRAMEWORKS}" "")
# Append to aggregated values variable: Use CONAN_LIBS instead of CONAN_PKG_LIBS to include user appended vars
set(CONAN_LIBS ${CONAN_LIBS} ${CONAN_SYSTEM_LIBS} ${CONAN_FRAMEWORKS_FOUND})


###  Definition of macros and functions ###

macro(conan_define_targets)
    if(${CMAKE_VERSION} VERSION_LESS "3.1.2")
        message(FATAL_ERROR "TARGETS not supported by your CMake version!")
    endif()  # CMAKE > 3.x
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CONAN_CMD_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CONAN_CMD_C_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CONAN_CMD_SHARED_LINKER_FLAGS}")


    set(_CONAN_PKG_LIBS_GLFW_DEPENDENCIES "${CONAN_SYSTEM_LIBS_GLFW} ${CONAN_FRAMEWORKS_FOUND_GLFW} CONAN_PKG::libx11 CONAN_PKG::libxrandr CONAN_PKG::libxinerama CONAN_PKG::libxcursor CONAN_PKG::libxi CONAN_PKG::mesa")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLFW_DEPENDENCIES "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLFW}" "${CONAN_LIB_DIRS_GLFW}"
                                  CONAN_PACKAGE_TARGETS_GLFW "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES}"
                                  "" glfw)
    set(_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_GLFW_DEBUG} ${CONAN_FRAMEWORKS_FOUND_GLFW_DEBUG} CONAN_PKG::libx11 CONAN_PKG::libxrandr CONAN_PKG::libxinerama CONAN_PKG::libxcursor CONAN_PKG::libxi CONAN_PKG::mesa")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLFW_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLFW_DEBUG}" "${CONAN_LIB_DIRS_GLFW_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_GLFW_DEBUG "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_DEBUG}"
                                  "debug" glfw)
    set(_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_GLFW_RELEASE} ${CONAN_FRAMEWORKS_FOUND_GLFW_RELEASE} CONAN_PKG::libx11 CONAN_PKG::libxrandr CONAN_PKG::libxinerama CONAN_PKG::libxcursor CONAN_PKG::libxi CONAN_PKG::mesa")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLFW_RELEASE}" "${CONAN_LIB_DIRS_GLFW_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_GLFW_RELEASE "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELEASE}"
                                  "release" glfw)
    set(_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_GLFW_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_GLFW_RELWITHDEBINFO} CONAN_PKG::libx11 CONAN_PKG::libxrandr CONAN_PKG::libxinerama CONAN_PKG::libxcursor CONAN_PKG::libxi CONAN_PKG::mesa")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLFW_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_GLFW_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_GLFW_RELWITHDEBINFO "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" glfw)
    set(_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_GLFW_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_GLFW_MINSIZEREL} CONAN_PKG::libx11 CONAN_PKG::libxrandr CONAN_PKG::libxinerama CONAN_PKG::libxcursor CONAN_PKG::libxi CONAN_PKG::mesa")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLFW_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLFW_MINSIZEREL}" "${CONAN_LIB_DIRS_GLFW_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_GLFW_MINSIZEREL "${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" glfw)

    add_library(CONAN_PKG::glfw INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::glfw PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_GLFW} ${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_GLFW_LIST} ${CONAN_EXE_LINKER_FLAGS_GLFW_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_GLFW_RELEASE} ${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_GLFW_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_GLFW_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_GLFW_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_GLFW_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_GLFW_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_GLFW_MINSIZEREL} ${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_GLFW_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_GLFW_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_GLFW_DEBUG} ${_CONAN_PKG_LIBS_GLFW_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_GLFW_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_GLFW_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::glfw PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_GLFW}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_GLFW_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_GLFW_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_GLFW_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_GLFW_DEBUG}>)
    set_property(TARGET CONAN_PKG::glfw PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_GLFW}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_GLFW_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_GLFW_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_GLFW_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_GLFW_DEBUG}>)
    set_property(TARGET CONAN_PKG::glfw PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_GLFW_LIST} ${CONAN_CXX_FLAGS_GLFW_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_GLFW_RELEASE_LIST} ${CONAN_CXX_FLAGS_GLFW_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_GLFW_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_GLFW_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_GLFW_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_GLFW_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_GLFW_DEBUG_LIST}  ${CONAN_CXX_FLAGS_GLFW_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXINERAMA} ${CONAN_FRAMEWORKS_FOUND_LIBXINERAMA} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXINERAMA}" "${CONAN_LIB_DIRS_LIBXINERAMA}"
                                  CONAN_PACKAGE_TARGETS_LIBXINERAMA "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES}"
                                  "" libxinerama)
    set(_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXINERAMA_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXINERAMA_DEBUG} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXINERAMA_DEBUG}" "${CONAN_LIB_DIRS_LIBXINERAMA_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXINERAMA_DEBUG "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_DEBUG}"
                                  "debug" libxinerama)
    set(_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXINERAMA_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXINERAMA_RELEASE} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXINERAMA_RELEASE}" "${CONAN_LIB_DIRS_LIBXINERAMA_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXINERAMA_RELEASE "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELEASE}"
                                  "release" libxinerama)
    set(_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXINERAMA_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXINERAMA_RELWITHDEBINFO} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXINERAMA_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXINERAMA_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXINERAMA_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxinerama)
    set(_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXINERAMA_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXINERAMA_MINSIZEREL} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXINERAMA_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXINERAMA_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXINERAMA_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxinerama)

    add_library(CONAN_PKG::libxinerama INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxinerama PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXINERAMA} ${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXINERAMA_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXINERAMA_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXINERAMA_RELEASE} ${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXINERAMA_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXINERAMA_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXINERAMA_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXINERAMA_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXINERAMA_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXINERAMA_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXINERAMA_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXINERAMA_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXINERAMA_DEBUG} ${_CONAN_PKG_LIBS_LIBXINERAMA_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXINERAMA_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXINERAMA_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxinerama PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXINERAMA}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXINERAMA_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXINERAMA_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXINERAMA_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXINERAMA_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxinerama PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXINERAMA}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXINERAMA_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXINERAMA_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXINERAMA_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXINERAMA_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxinerama PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXINERAMA_LIST} ${CONAN_CXX_FLAGS_LIBXINERAMA_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXINERAMA_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXINERAMA_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXINERAMA_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXINERAMA_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXINERAMA_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXINERAMA_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXINERAMA_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXINERAMA_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXCURSOR} ${CONAN_FRAMEWORKS_FOUND_LIBXCURSOR} CONAN_PKG::libxfixes CONAN_PKG::libxrender")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCURSOR}" "${CONAN_LIB_DIRS_LIBXCURSOR}"
                                  CONAN_PACKAGE_TARGETS_LIBXCURSOR "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES}"
                                  "" libxcursor)
    set(_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXCURSOR_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXCURSOR_DEBUG} CONAN_PKG::libxfixes CONAN_PKG::libxrender")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCURSOR_DEBUG}" "${CONAN_LIB_DIRS_LIBXCURSOR_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXCURSOR_DEBUG "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_DEBUG}"
                                  "debug" libxcursor)
    set(_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXCURSOR_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXCURSOR_RELEASE} CONAN_PKG::libxfixes CONAN_PKG::libxrender")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCURSOR_RELEASE}" "${CONAN_LIB_DIRS_LIBXCURSOR_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXCURSOR_RELEASE "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELEASE}"
                                  "release" libxcursor)
    set(_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXCURSOR_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXCURSOR_RELWITHDEBINFO} CONAN_PKG::libxfixes CONAN_PKG::libxrender")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCURSOR_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXCURSOR_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXCURSOR_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxcursor)
    set(_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXCURSOR_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXCURSOR_MINSIZEREL} CONAN_PKG::libxfixes CONAN_PKG::libxrender")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCURSOR_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXCURSOR_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXCURSOR_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxcursor)

    add_library(CONAN_PKG::libxcursor INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxcursor PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXCURSOR} ${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXCURSOR_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCURSOR_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXCURSOR_RELEASE} ${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXCURSOR_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCURSOR_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXCURSOR_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXCURSOR_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCURSOR_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXCURSOR_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXCURSOR_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCURSOR_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXCURSOR_DEBUG} ${_CONAN_PKG_LIBS_LIBXCURSOR_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXCURSOR_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCURSOR_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxcursor PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXCURSOR}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXCURSOR_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXCURSOR_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXCURSOR_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXCURSOR_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxcursor PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXCURSOR}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXCURSOR_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXCURSOR_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXCURSOR_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXCURSOR_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxcursor PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXCURSOR_LIST} ${CONAN_CXX_FLAGS_LIBXCURSOR_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXCURSOR_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXCURSOR_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXCURSOR_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXCURSOR_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXCURSOR_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXCURSOR_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXCURSOR_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXCURSOR_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXI} ${CONAN_FRAMEWORKS_FOUND_LIBXI} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXI_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXI}" "${CONAN_LIB_DIRS_LIBXI}"
                                  CONAN_PACKAGE_TARGETS_LIBXI "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES}"
                                  "" libxi)
    set(_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXI_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXI_DEBUG} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXI_DEBUG}" "${CONAN_LIB_DIRS_LIBXI_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXI_DEBUG "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_DEBUG}"
                                  "debug" libxi)
    set(_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXI_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXI_RELEASE} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXI_RELEASE}" "${CONAN_LIB_DIRS_LIBXI_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXI_RELEASE "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELEASE}"
                                  "release" libxi)
    set(_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXI_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXI_RELWITHDEBINFO} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXI_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXI_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXI_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxi)
    set(_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXI_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXI_MINSIZEREL} CONAN_PKG::libxext CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXI_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXI_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXI_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxi)

    add_library(CONAN_PKG::libxi INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxi PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXI} ${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXI_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXI_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXI_RELEASE} ${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXI_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXI_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXI_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXI_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXI_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXI_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXI_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXI_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXI_DEBUG} ${_CONAN_PKG_LIBS_LIBXI_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXI_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXI_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxi PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXI}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXI_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXI_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXI_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXI_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxi PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXI}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXI_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXI_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXI_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXI_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxi PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXI_LIST} ${CONAN_CXX_FLAGS_LIBXI_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXI_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXI_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXI_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXI_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXI_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXI_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXI_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXI_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_MESA_DEPENDENCIES "${CONAN_SYSTEM_LIBS_MESA} ${CONAN_FRAMEWORKS_FOUND_MESA} CONAN_PKG::zlib CONAN_PKG::expat CONAN_PKG::libdrm CONAN_PKG::libelf CONAN_PKG::libunwind CONAN_PKG::libx11 CONAN_PKG::libxext CONAN_PKG::libxdamage CONAN_PKG::libxfixes CONAN_PKG::libxcb CONAN_PKG::libxshmfence CONAN_PKG::libxxf86vm CONAN_PKG::libxrandr")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_MESA_DEPENDENCIES "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_MESA}" "${CONAN_LIB_DIRS_MESA}"
                                  CONAN_PACKAGE_TARGETS_MESA "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES}"
                                  "" mesa)
    set(_CONAN_PKG_LIBS_MESA_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_MESA_DEBUG} ${CONAN_FRAMEWORKS_FOUND_MESA_DEBUG} CONAN_PKG::zlib CONAN_PKG::expat CONAN_PKG::libdrm CONAN_PKG::libelf CONAN_PKG::libunwind CONAN_PKG::libx11 CONAN_PKG::libxext CONAN_PKG::libxdamage CONAN_PKG::libxfixes CONAN_PKG::libxcb CONAN_PKG::libxshmfence CONAN_PKG::libxxf86vm CONAN_PKG::libxrandr")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_MESA_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_MESA_DEBUG}" "${CONAN_LIB_DIRS_MESA_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_MESA_DEBUG "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_DEBUG}"
                                  "debug" mesa)
    set(_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_MESA_RELEASE} ${CONAN_FRAMEWORKS_FOUND_MESA_RELEASE} CONAN_PKG::zlib CONAN_PKG::expat CONAN_PKG::libdrm CONAN_PKG::libelf CONAN_PKG::libunwind CONAN_PKG::libx11 CONAN_PKG::libxext CONAN_PKG::libxdamage CONAN_PKG::libxfixes CONAN_PKG::libxcb CONAN_PKG::libxshmfence CONAN_PKG::libxxf86vm CONAN_PKG::libxrandr")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_MESA_RELEASE}" "${CONAN_LIB_DIRS_MESA_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_MESA_RELEASE "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELEASE}"
                                  "release" mesa)
    set(_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_MESA_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_MESA_RELWITHDEBINFO} CONAN_PKG::zlib CONAN_PKG::expat CONAN_PKG::libdrm CONAN_PKG::libelf CONAN_PKG::libunwind CONAN_PKG::libx11 CONAN_PKG::libxext CONAN_PKG::libxdamage CONAN_PKG::libxfixes CONAN_PKG::libxcb CONAN_PKG::libxshmfence CONAN_PKG::libxxf86vm CONAN_PKG::libxrandr")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_MESA_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_MESA_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_MESA_RELWITHDEBINFO "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" mesa)
    set(_CONAN_PKG_LIBS_MESA_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_MESA_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_MESA_MINSIZEREL} CONAN_PKG::zlib CONAN_PKG::expat CONAN_PKG::libdrm CONAN_PKG::libelf CONAN_PKG::libunwind CONAN_PKG::libx11 CONAN_PKG::libxext CONAN_PKG::libxdamage CONAN_PKG::libxfixes CONAN_PKG::libxcb CONAN_PKG::libxshmfence CONAN_PKG::libxxf86vm CONAN_PKG::libxrandr")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_MESA_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_MESA_MINSIZEREL}" "${CONAN_LIB_DIRS_MESA_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_MESA_MINSIZEREL "${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" mesa)

    add_library(CONAN_PKG::mesa INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::mesa PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_MESA} ${_CONAN_PKG_LIBS_MESA_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_MESA_LIST} ${CONAN_EXE_LINKER_FLAGS_MESA_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_MESA_RELEASE} ${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_MESA_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_MESA_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_MESA_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_MESA_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_MESA_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_MESA_MINSIZEREL} ${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_MESA_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_MESA_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_MESA_DEBUG} ${_CONAN_PKG_LIBS_MESA_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_MESA_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_MESA_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::mesa PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_MESA}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_MESA_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_MESA_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_MESA_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_MESA_DEBUG}>)
    set_property(TARGET CONAN_PKG::mesa PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_MESA}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_MESA_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_MESA_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_MESA_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_MESA_DEBUG}>)
    set_property(TARGET CONAN_PKG::mesa PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_MESA_LIST} ${CONAN_CXX_FLAGS_MESA_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_MESA_RELEASE_LIST} ${CONAN_CXX_FLAGS_MESA_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_MESA_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_MESA_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_MESA_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_MESA_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_MESA_DEBUG_LIST}  ${CONAN_CXX_FLAGS_MESA_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXRANDR} ${CONAN_FRAMEWORKS_FOUND_LIBXRANDR} CONAN_PKG::libxrender CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRANDR}" "${CONAN_LIB_DIRS_LIBXRANDR}"
                                  CONAN_PACKAGE_TARGETS_LIBXRANDR "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES}"
                                  "" libxrandr)
    set(_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXRANDR_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXRANDR_DEBUG} CONAN_PKG::libxrender CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRANDR_DEBUG}" "${CONAN_LIB_DIRS_LIBXRANDR_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXRANDR_DEBUG "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_DEBUG}"
                                  "debug" libxrandr)
    set(_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXRANDR_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXRANDR_RELEASE} CONAN_PKG::libxrender CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRANDR_RELEASE}" "${CONAN_LIB_DIRS_LIBXRANDR_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXRANDR_RELEASE "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELEASE}"
                                  "release" libxrandr)
    set(_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXRANDR_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXRANDR_RELWITHDEBINFO} CONAN_PKG::libxrender CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRANDR_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXRANDR_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXRANDR_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxrandr)
    set(_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXRANDR_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXRANDR_MINSIZEREL} CONAN_PKG::libxrender CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRANDR_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXRANDR_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXRANDR_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxrandr)

    add_library(CONAN_PKG::libxrandr INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxrandr PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXRANDR} ${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXRANDR_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRANDR_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXRANDR_RELEASE} ${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXRANDR_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRANDR_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXRANDR_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXRANDR_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRANDR_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXRANDR_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXRANDR_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRANDR_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXRANDR_DEBUG} ${_CONAN_PKG_LIBS_LIBXRANDR_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXRANDR_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRANDR_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxrandr PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXRANDR}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXRANDR_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXRANDR_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXRANDR_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXRANDR_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxrandr PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXRANDR}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXRANDR_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXRANDR_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXRANDR_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXRANDR_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxrandr PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXRANDR_LIST} ${CONAN_CXX_FLAGS_LIBXRANDR_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXRANDR_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXRANDR_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXRANDR_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXRANDR_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXRANDR_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXRANDR_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXRANDR_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXRANDR_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES "${CONAN_SYSTEM_LIBS_ZLIB} ${CONAN_FRAMEWORKS_FOUND_ZLIB} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB}" "${CONAN_LIB_DIRS_ZLIB}"
                                  CONAN_PACKAGE_TARGETS_ZLIB "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES}"
                                  "" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_ZLIB_DEBUG} ${CONAN_FRAMEWORKS_FOUND_ZLIB_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_DEBUG}" "${CONAN_LIB_DIRS_ZLIB_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_DEBUG "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG}"
                                  "debug" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_ZLIB_RELEASE} ${CONAN_FRAMEWORKS_FOUND_ZLIB_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_RELEASE}" "${CONAN_LIB_DIRS_ZLIB_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_RELEASE "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE}"
                                  "release" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_ZLIB_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_ZLIB_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_ZLIB_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_RELWITHDEBINFO "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_ZLIB_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_ZLIB_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_MINSIZEREL}" "${CONAN_LIB_DIRS_ZLIB_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_MINSIZEREL "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" zlib)

    add_library(CONAN_PKG::zlib INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_ZLIB} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_ZLIB_LIST} ${CONAN_EXE_LINKER_FLAGS_ZLIB_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_ZLIB_RELEASE} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_ZLIB_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_ZLIB_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_ZLIB_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_ZLIB_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_ZLIB_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_ZLIB_MINSIZEREL} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_ZLIB_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_ZLIB_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_ZLIB_DEBUG} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_ZLIB_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_ZLIB_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_ZLIB}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_ZLIB_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_ZLIB_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_ZLIB_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_ZLIB_DEBUG}>)
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_ZLIB}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_ZLIB_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_ZLIB_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_ZLIB_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_ZLIB_DEBUG}>)
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_ZLIB_LIST} ${CONAN_CXX_FLAGS_ZLIB_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_ZLIB_RELEASE_LIST} ${CONAN_CXX_FLAGS_ZLIB_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_ZLIB_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_ZLIB_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_ZLIB_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_ZLIB_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_ZLIB_DEBUG_LIST}  ${CONAN_CXX_FLAGS_ZLIB_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES "${CONAN_SYSTEM_LIBS_EXPAT} ${CONAN_FRAMEWORKS_FOUND_EXPAT} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_EXPAT_DEPENDENCIES "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_EXPAT}" "${CONAN_LIB_DIRS_EXPAT}"
                                  CONAN_PACKAGE_TARGETS_EXPAT "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES}"
                                  "" expat)
    set(_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_EXPAT_DEBUG} ${CONAN_FRAMEWORKS_FOUND_EXPAT_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_EXPAT_DEBUG}" "${CONAN_LIB_DIRS_EXPAT_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_EXPAT_DEBUG "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_DEBUG}"
                                  "debug" expat)
    set(_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_EXPAT_RELEASE} ${CONAN_FRAMEWORKS_FOUND_EXPAT_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_EXPAT_RELEASE}" "${CONAN_LIB_DIRS_EXPAT_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_EXPAT_RELEASE "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELEASE}"
                                  "release" expat)
    set(_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_EXPAT_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_EXPAT_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_EXPAT_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_EXPAT_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_EXPAT_RELWITHDEBINFO "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" expat)
    set(_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_EXPAT_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_EXPAT_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_EXPAT_MINSIZEREL}" "${CONAN_LIB_DIRS_EXPAT_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_EXPAT_MINSIZEREL "${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" expat)

    add_library(CONAN_PKG::expat INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::expat PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_EXPAT} ${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_EXPAT_LIST} ${CONAN_EXE_LINKER_FLAGS_EXPAT_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_EXPAT_RELEASE} ${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_EXPAT_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_EXPAT_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_EXPAT_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_EXPAT_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_EXPAT_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_EXPAT_MINSIZEREL} ${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_EXPAT_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_EXPAT_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_EXPAT_DEBUG} ${_CONAN_PKG_LIBS_EXPAT_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_EXPAT_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_EXPAT_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::expat PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_EXPAT}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_EXPAT_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_EXPAT_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_EXPAT_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_EXPAT_DEBUG}>)
    set_property(TARGET CONAN_PKG::expat PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_EXPAT}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_EXPAT_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_EXPAT_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_EXPAT_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_EXPAT_DEBUG}>)
    set_property(TARGET CONAN_PKG::expat PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_EXPAT_LIST} ${CONAN_CXX_FLAGS_EXPAT_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_EXPAT_RELEASE_LIST} ${CONAN_CXX_FLAGS_EXPAT_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_EXPAT_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_EXPAT_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_EXPAT_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_EXPAT_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_EXPAT_DEBUG_LIST}  ${CONAN_CXX_FLAGS_EXPAT_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBDRM} ${CONAN_FRAMEWORKS_FOUND_LIBDRM} CONAN_PKG::libpciaccess")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBDRM}" "${CONAN_LIB_DIRS_LIBDRM}"
                                  CONAN_PACKAGE_TARGETS_LIBDRM "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES}"
                                  "" libdrm)
    set(_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBDRM_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBDRM_DEBUG} CONAN_PKG::libpciaccess")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBDRM_DEBUG}" "${CONAN_LIB_DIRS_LIBDRM_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBDRM_DEBUG "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_DEBUG}"
                                  "debug" libdrm)
    set(_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBDRM_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBDRM_RELEASE} CONAN_PKG::libpciaccess")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBDRM_RELEASE}" "${CONAN_LIB_DIRS_LIBDRM_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBDRM_RELEASE "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELEASE}"
                                  "release" libdrm)
    set(_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBDRM_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBDRM_RELWITHDEBINFO} CONAN_PKG::libpciaccess")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBDRM_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBDRM_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBDRM_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libdrm)
    set(_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBDRM_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBDRM_MINSIZEREL} CONAN_PKG::libpciaccess")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBDRM_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBDRM_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBDRM_MINSIZEREL "${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libdrm)

    add_library(CONAN_PKG::libdrm INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libdrm PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBDRM} ${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBDRM_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBDRM_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBDRM_RELEASE} ${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBDRM_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBDRM_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBDRM_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBDRM_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBDRM_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBDRM_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBDRM_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBDRM_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBDRM_DEBUG} ${_CONAN_PKG_LIBS_LIBDRM_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBDRM_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBDRM_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libdrm PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBDRM}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBDRM_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBDRM_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBDRM_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBDRM_DEBUG}>)
    set_property(TARGET CONAN_PKG::libdrm PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBDRM}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBDRM_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBDRM_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBDRM_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBDRM_DEBUG}>)
    set_property(TARGET CONAN_PKG::libdrm PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBDRM_LIST} ${CONAN_CXX_FLAGS_LIBDRM_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBDRM_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBDRM_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBDRM_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBDRM_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBDRM_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBDRM_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBDRM_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBDRM_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBELF} ${CONAN_FRAMEWORKS_FOUND_LIBELF} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBELF_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBELF}" "${CONAN_LIB_DIRS_LIBELF}"
                                  CONAN_PACKAGE_TARGETS_LIBELF "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES}"
                                  "" libelf)
    set(_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBELF_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBELF_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBELF_DEBUG}" "${CONAN_LIB_DIRS_LIBELF_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBELF_DEBUG "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_DEBUG}"
                                  "debug" libelf)
    set(_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBELF_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBELF_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBELF_RELEASE}" "${CONAN_LIB_DIRS_LIBELF_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBELF_RELEASE "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELEASE}"
                                  "release" libelf)
    set(_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBELF_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBELF_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBELF_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBELF_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBELF_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libelf)
    set(_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBELF_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBELF_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBELF_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBELF_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBELF_MINSIZEREL "${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libelf)

    add_library(CONAN_PKG::libelf INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libelf PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBELF} ${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBELF_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBELF_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBELF_RELEASE} ${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBELF_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBELF_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBELF_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBELF_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBELF_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBELF_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBELF_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBELF_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBELF_DEBUG} ${_CONAN_PKG_LIBS_LIBELF_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBELF_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBELF_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libelf PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBELF}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBELF_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBELF_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBELF_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBELF_DEBUG}>)
    set_property(TARGET CONAN_PKG::libelf PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBELF}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBELF_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBELF_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBELF_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBELF_DEBUG}>)
    set_property(TARGET CONAN_PKG::libelf PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBELF_LIST} ${CONAN_CXX_FLAGS_LIBELF_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBELF_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBELF_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBELF_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBELF_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBELF_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBELF_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBELF_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBELF_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBUNWIND} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND} CONAN_PKG::xz_utils")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND}" "${CONAN_LIB_DIRS_LIBUNWIND}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES}"
                                  "" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBUNWIND_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_DEBUG} CONAN_PKG::xz_utils")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_DEBUG}" "${CONAN_LIB_DIRS_LIBUNWIND_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_DEBUG "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG}"
                                  "debug" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBUNWIND_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_RELEASE} CONAN_PKG::xz_utils")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_RELEASE}" "${CONAN_LIB_DIRS_LIBUNWIND_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_RELEASE "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE}"
                                  "release" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBUNWIND_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_RELWITHDEBINFO} CONAN_PKG::xz_utils")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBUNWIND_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBUNWIND_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_MINSIZEREL} CONAN_PKG::xz_utils")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBUNWIND_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_MINSIZEREL "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libunwind)

    add_library(CONAN_PKG::libunwind INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBUNWIND} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_RELEASE} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_DEBUG} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBUNWIND}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBUNWIND_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBUNWIND_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBUNWIND_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBUNWIND_DEBUG}>)
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBUNWIND}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_DEBUG}>)
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBUNWIND_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBUNWIND_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBUNWIND_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBUNWIND_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBUNWIND_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXDAMAGE} ${CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE} CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDAMAGE}" "${CONAN_LIB_DIRS_LIBXDAMAGE}"
                                  CONAN_PACKAGE_TARGETS_LIBXDAMAGE "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES}"
                                  "" libxdamage)
    set(_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXDAMAGE_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE_DEBUG} CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDAMAGE_DEBUG}" "${CONAN_LIB_DIRS_LIBXDAMAGE_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXDAMAGE_DEBUG "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_DEBUG}"
                                  "debug" libxdamage)
    set(_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXDAMAGE_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE_RELEASE} CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDAMAGE_RELEASE}" "${CONAN_LIB_DIRS_LIBXDAMAGE_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXDAMAGE_RELEASE "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELEASE}"
                                  "release" libxdamage)
    set(_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXDAMAGE_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE_RELWITHDEBINFO} CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDAMAGE_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXDAMAGE_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXDAMAGE_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxdamage)
    set(_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXDAMAGE_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXDAMAGE_MINSIZEREL} CONAN_PKG::libxfixes")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDAMAGE_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXDAMAGE_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXDAMAGE_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxdamage)

    add_library(CONAN_PKG::libxdamage INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxdamage PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXDAMAGE} ${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXDAMAGE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDAMAGE_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXDAMAGE_RELEASE} ${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXDAMAGE_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDAMAGE_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXDAMAGE_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXDAMAGE_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDAMAGE_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXDAMAGE_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXDAMAGE_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDAMAGE_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXDAMAGE_DEBUG} ${_CONAN_PKG_LIBS_LIBXDAMAGE_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXDAMAGE_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDAMAGE_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxdamage PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXDAMAGE}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXDAMAGE_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXDAMAGE_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXDAMAGE_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXDAMAGE_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxdamage PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXDAMAGE}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXDAMAGE_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXDAMAGE_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXDAMAGE_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXDAMAGE_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxdamage PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXDAMAGE_LIST} ${CONAN_CXX_FLAGS_LIBXDAMAGE_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXDAMAGE_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXDAMAGE_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXDAMAGE_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXDAMAGE_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXDAMAGE_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXDAMAGE_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXDAMAGE_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXDAMAGE_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXSHMFENCE} ${CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE} CONAN_PKG::xorgproto CONAN_PKG::util-macros")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXSHMFENCE}" "${CONAN_LIB_DIRS_LIBXSHMFENCE}"
                                  CONAN_PACKAGE_TARGETS_LIBXSHMFENCE "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES}"
                                  "" libxshmfence)
    set(_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXSHMFENCE_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE_DEBUG} CONAN_PKG::xorgproto CONAN_PKG::util-macros")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXSHMFENCE_DEBUG}" "${CONAN_LIB_DIRS_LIBXSHMFENCE_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_DEBUG "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_DEBUG}"
                                  "debug" libxshmfence)
    set(_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXSHMFENCE_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE_RELEASE} CONAN_PKG::xorgproto CONAN_PKG::util-macros")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXSHMFENCE_RELEASE}" "${CONAN_LIB_DIRS_LIBXSHMFENCE_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_RELEASE "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELEASE}"
                                  "release" libxshmfence)
    set(_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXSHMFENCE_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE_RELWITHDEBINFO} CONAN_PKG::xorgproto CONAN_PKG::util-macros")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXSHMFENCE_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXSHMFENCE_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxshmfence)
    set(_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXSHMFENCE_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXSHMFENCE_MINSIZEREL} CONAN_PKG::xorgproto CONAN_PKG::util-macros")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXSHMFENCE_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXSHMFENCE_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxshmfence)

    add_library(CONAN_PKG::libxshmfence INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxshmfence PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXSHMFENCE} ${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXSHMFENCE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXSHMFENCE_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_RELEASE} ${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXSHMFENCE_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXSHMFENCE_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXSHMFENCE_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXSHMFENCE_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXSHMFENCE_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXSHMFENCE_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXSHMFENCE_DEBUG} ${_CONAN_PKG_LIBS_LIBXSHMFENCE_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXSHMFENCE_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXSHMFENCE_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxshmfence PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXSHMFENCE}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXSHMFENCE_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXSHMFENCE_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXSHMFENCE_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXSHMFENCE_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxshmfence PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXSHMFENCE}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXSHMFENCE_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXSHMFENCE_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXSHMFENCE_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXSHMFENCE_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxshmfence PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXSHMFENCE_LIST} ${CONAN_CXX_FLAGS_LIBXSHMFENCE_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXSHMFENCE_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXSHMFENCE_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXSHMFENCE_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXSHMFENCE_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXSHMFENCE_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXSHMFENCE_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXSHMFENCE_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXSHMFENCE_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXXF86VM} ${CONAN_FRAMEWORKS_FOUND_LIBXXF86VM} CONAN_PKG::libx11 CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXXF86VM}" "${CONAN_LIB_DIRS_LIBXXF86VM}"
                                  CONAN_PACKAGE_TARGETS_LIBXXF86VM "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES}"
                                  "" libxxf86vm)
    set(_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXXF86VM_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXXF86VM_DEBUG} CONAN_PKG::libx11 CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXXF86VM_DEBUG}" "${CONAN_LIB_DIRS_LIBXXF86VM_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXXF86VM_DEBUG "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_DEBUG}"
                                  "debug" libxxf86vm)
    set(_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXXF86VM_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXXF86VM_RELEASE} CONAN_PKG::libx11 CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXXF86VM_RELEASE}" "${CONAN_LIB_DIRS_LIBXXF86VM_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXXF86VM_RELEASE "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELEASE}"
                                  "release" libxxf86vm)
    set(_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXXF86VM_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXXF86VM_RELWITHDEBINFO} CONAN_PKG::libx11 CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXXF86VM_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXXF86VM_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXXF86VM_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxxf86vm)
    set(_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXXF86VM_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXXF86VM_MINSIZEREL} CONAN_PKG::libx11 CONAN_PKG::libxext")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXXF86VM_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXXF86VM_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXXF86VM_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxxf86vm)

    add_library(CONAN_PKG::libxxf86vm INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxxf86vm PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXXF86VM} ${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXXF86VM_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXXF86VM_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXXF86VM_RELEASE} ${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXXF86VM_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXXF86VM_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXXF86VM_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXXF86VM_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXXF86VM_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXXF86VM_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXXF86VM_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXXF86VM_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXXF86VM_DEBUG} ${_CONAN_PKG_LIBS_LIBXXF86VM_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXXF86VM_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXXF86VM_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxxf86vm PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXXF86VM}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXXF86VM_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXXF86VM_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXXF86VM_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXXF86VM_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxxf86vm PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXXF86VM}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXXF86VM_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXXF86VM_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXXF86VM_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXXF86VM_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxxf86vm PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXXF86VM_LIST} ${CONAN_CXX_FLAGS_LIBXXF86VM_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXXF86VM_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXXF86VM_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXXF86VM_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXXF86VM_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXXF86VM_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXXF86VM_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXXF86VM_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXXF86VM_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXRENDER} ${CONAN_FRAMEWORKS_FOUND_LIBXRENDER} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRENDER}" "${CONAN_LIB_DIRS_LIBXRENDER}"
                                  CONAN_PACKAGE_TARGETS_LIBXRENDER "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES}"
                                  "" libxrender)
    set(_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXRENDER_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXRENDER_DEBUG} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRENDER_DEBUG}" "${CONAN_LIB_DIRS_LIBXRENDER_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXRENDER_DEBUG "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_DEBUG}"
                                  "debug" libxrender)
    set(_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXRENDER_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXRENDER_RELEASE} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRENDER_RELEASE}" "${CONAN_LIB_DIRS_LIBXRENDER_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXRENDER_RELEASE "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELEASE}"
                                  "release" libxrender)
    set(_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXRENDER_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXRENDER_RELWITHDEBINFO} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRENDER_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXRENDER_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXRENDER_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxrender)
    set(_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXRENDER_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXRENDER_MINSIZEREL} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXRENDER_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXRENDER_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXRENDER_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxrender)

    add_library(CONAN_PKG::libxrender INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxrender PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXRENDER} ${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXRENDER_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRENDER_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXRENDER_RELEASE} ${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXRENDER_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRENDER_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXRENDER_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXRENDER_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRENDER_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXRENDER_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXRENDER_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRENDER_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXRENDER_DEBUG} ${_CONAN_PKG_LIBS_LIBXRENDER_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXRENDER_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXRENDER_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxrender PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXRENDER}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXRENDER_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXRENDER_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXRENDER_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXRENDER_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxrender PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXRENDER}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXRENDER_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXRENDER_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXRENDER_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXRENDER_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxrender PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXRENDER_LIST} ${CONAN_CXX_FLAGS_LIBXRENDER_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXRENDER_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXRENDER_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXRENDER_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXRENDER_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXRENDER_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXRENDER_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXRENDER_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXRENDER_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXEXT} ${CONAN_FRAMEWORKS_FOUND_LIBXEXT} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXEXT}" "${CONAN_LIB_DIRS_LIBXEXT}"
                                  CONAN_PACKAGE_TARGETS_LIBXEXT "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES}"
                                  "" libxext)
    set(_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXEXT_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXEXT_DEBUG} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXEXT_DEBUG}" "${CONAN_LIB_DIRS_LIBXEXT_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXEXT_DEBUG "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_DEBUG}"
                                  "debug" libxext)
    set(_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXEXT_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXEXT_RELEASE} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXEXT_RELEASE}" "${CONAN_LIB_DIRS_LIBXEXT_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXEXT_RELEASE "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELEASE}"
                                  "release" libxext)
    set(_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXEXT_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXEXT_RELWITHDEBINFO} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXEXT_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXEXT_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXEXT_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxext)
    set(_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXEXT_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXEXT_MINSIZEREL} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXEXT_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXEXT_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXEXT_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxext)

    add_library(CONAN_PKG::libxext INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxext PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXEXT} ${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXEXT_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXEXT_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXEXT_RELEASE} ${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXEXT_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXEXT_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXEXT_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXEXT_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXEXT_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXEXT_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXEXT_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXEXT_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXEXT_DEBUG} ${_CONAN_PKG_LIBS_LIBXEXT_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXEXT_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXEXT_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxext PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXEXT}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXEXT_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXEXT_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXEXT_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXEXT_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxext PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXEXT}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXEXT_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXEXT_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXEXT_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXEXT_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxext PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXEXT_LIST} ${CONAN_CXX_FLAGS_LIBXEXT_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXEXT_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXEXT_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXEXT_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXEXT_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXEXT_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXEXT_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXEXT_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXEXT_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXFIXES} ${CONAN_FRAMEWORKS_FOUND_LIBXFIXES} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXFIXES}" "${CONAN_LIB_DIRS_LIBXFIXES}"
                                  CONAN_PACKAGE_TARGETS_LIBXFIXES "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES}"
                                  "" libxfixes)
    set(_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXFIXES_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXFIXES_DEBUG} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXFIXES_DEBUG}" "${CONAN_LIB_DIRS_LIBXFIXES_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXFIXES_DEBUG "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_DEBUG}"
                                  "debug" libxfixes)
    set(_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXFIXES_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXFIXES_RELEASE} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXFIXES_RELEASE}" "${CONAN_LIB_DIRS_LIBXFIXES_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXFIXES_RELEASE "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELEASE}"
                                  "release" libxfixes)
    set(_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXFIXES_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXFIXES_RELWITHDEBINFO} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXFIXES_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXFIXES_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXFIXES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxfixes)
    set(_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXFIXES_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXFIXES_MINSIZEREL} CONAN_PKG::libx11")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXFIXES_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXFIXES_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXFIXES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxfixes)

    add_library(CONAN_PKG::libxfixes INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxfixes PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXFIXES} ${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXFIXES_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXFIXES_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXFIXES_RELEASE} ${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXFIXES_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXFIXES_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXFIXES_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXFIXES_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXFIXES_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXFIXES_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXFIXES_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXFIXES_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXFIXES_DEBUG} ${_CONAN_PKG_LIBS_LIBXFIXES_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXFIXES_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXFIXES_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxfixes PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXFIXES}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXFIXES_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXFIXES_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXFIXES_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXFIXES_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxfixes PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXFIXES}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXFIXES_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXFIXES_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXFIXES_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXFIXES_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxfixes PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXFIXES_LIST} ${CONAN_CXX_FLAGS_LIBXFIXES_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXFIXES_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXFIXES_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXFIXES_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXFIXES_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXFIXES_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXFIXES_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXFIXES_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXFIXES_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBPCIACCESS} ${CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPCIACCESS}" "${CONAN_LIB_DIRS_LIBPCIACCESS}"
                                  CONAN_PACKAGE_TARGETS_LIBPCIACCESS "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES}"
                                  "" libpciaccess)
    set(_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBPCIACCESS_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPCIACCESS_DEBUG}" "${CONAN_LIB_DIRS_LIBPCIACCESS_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBPCIACCESS_DEBUG "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_DEBUG}"
                                  "debug" libpciaccess)
    set(_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBPCIACCESS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPCIACCESS_RELEASE}" "${CONAN_LIB_DIRS_LIBPCIACCESS_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBPCIACCESS_RELEASE "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELEASE}"
                                  "release" libpciaccess)
    set(_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBPCIACCESS_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPCIACCESS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBPCIACCESS_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBPCIACCESS_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libpciaccess)
    set(_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBPCIACCESS_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBPCIACCESS_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPCIACCESS_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBPCIACCESS_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBPCIACCESS_MINSIZEREL "${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libpciaccess)

    add_library(CONAN_PKG::libpciaccess INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libpciaccess PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBPCIACCESS} ${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBPCIACCESS_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPCIACCESS_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBPCIACCESS_RELEASE} ${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBPCIACCESS_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPCIACCESS_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBPCIACCESS_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBPCIACCESS_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPCIACCESS_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBPCIACCESS_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBPCIACCESS_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPCIACCESS_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBPCIACCESS_DEBUG} ${_CONAN_PKG_LIBS_LIBPCIACCESS_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBPCIACCESS_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPCIACCESS_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libpciaccess PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBPCIACCESS}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBPCIACCESS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBPCIACCESS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBPCIACCESS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBPCIACCESS_DEBUG}>)
    set_property(TARGET CONAN_PKG::libpciaccess PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBPCIACCESS}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBPCIACCESS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBPCIACCESS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBPCIACCESS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBPCIACCESS_DEBUG}>)
    set_property(TARGET CONAN_PKG::libpciaccess PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBPCIACCESS_LIST} ${CONAN_CXX_FLAGS_LIBPCIACCESS_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBPCIACCESS_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBPCIACCESS_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBPCIACCESS_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBPCIACCESS_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBPCIACCESS_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBPCIACCESS_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBPCIACCESS_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBPCIACCESS_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES "${CONAN_SYSTEM_LIBS_XZ_UTILS} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS}" "${CONAN_LIB_DIRS_XZ_UTILS}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES}"
                                  "" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_XZ_UTILS_DEBUG} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_DEBUG}" "${CONAN_LIB_DIRS_XZ_UTILS_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_DEBUG "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG}"
                                  "debug" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_XZ_UTILS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_RELEASE}" "${CONAN_LIB_DIRS_XZ_UTILS_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_RELEASE "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE}"
                                  "release" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_XZ_UTILS_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_XZ_UTILS_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_XZ_UTILS_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_MINSIZEREL}" "${CONAN_LIB_DIRS_XZ_UTILS_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_MINSIZEREL "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" xz_utils)

    add_library(CONAN_PKG::xz_utils INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_XZ_UTILS} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_LIST} ${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_RELEASE} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_MINSIZEREL} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_DEBUG} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_XZ_UTILS}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_XZ_UTILS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_XZ_UTILS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_XZ_UTILS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_XZ_UTILS_DEBUG}>)
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_XZ_UTILS}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_DEBUG}>)
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_XZ_UTILS_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_XZ_UTILS_RELEASE_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_XZ_UTILS_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_XZ_UTILS_DEBUG_LIST}  ${CONAN_CXX_FLAGS_XZ_UTILS_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBX11} ${CONAN_FRAMEWORKS_FOUND_LIBX11} CONAN_PKG::xorgproto CONAN_PKG::xtrans CONAN_PKG::libxcb")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBX11_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBX11}" "${CONAN_LIB_DIRS_LIBX11}"
                                  CONAN_PACKAGE_TARGETS_LIBX11 "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES}"
                                  "" libx11)
    set(_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBX11_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBX11_DEBUG} CONAN_PKG::xorgproto CONAN_PKG::xtrans CONAN_PKG::libxcb")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBX11_DEBUG}" "${CONAN_LIB_DIRS_LIBX11_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBX11_DEBUG "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_DEBUG}"
                                  "debug" libx11)
    set(_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBX11_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBX11_RELEASE} CONAN_PKG::xorgproto CONAN_PKG::xtrans CONAN_PKG::libxcb")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBX11_RELEASE}" "${CONAN_LIB_DIRS_LIBX11_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBX11_RELEASE "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELEASE}"
                                  "release" libx11)
    set(_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBX11_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBX11_RELWITHDEBINFO} CONAN_PKG::xorgproto CONAN_PKG::xtrans CONAN_PKG::libxcb")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBX11_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBX11_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBX11_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libx11)
    set(_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBX11_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBX11_MINSIZEREL} CONAN_PKG::xorgproto CONAN_PKG::xtrans CONAN_PKG::libxcb")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBX11_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBX11_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBX11_MINSIZEREL "${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libx11)

    add_library(CONAN_PKG::libx11 INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libx11 PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBX11} ${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBX11_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBX11_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBX11_RELEASE} ${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBX11_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBX11_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBX11_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBX11_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBX11_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBX11_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBX11_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBX11_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBX11_DEBUG} ${_CONAN_PKG_LIBS_LIBX11_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBX11_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBX11_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libx11 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBX11}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBX11_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBX11_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBX11_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBX11_DEBUG}>)
    set_property(TARGET CONAN_PKG::libx11 PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBX11}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBX11_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBX11_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBX11_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBX11_DEBUG}>)
    set_property(TARGET CONAN_PKG::libx11 PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBX11_LIST} ${CONAN_CXX_FLAGS_LIBX11_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBX11_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBX11_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBX11_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBX11_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBX11_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBX11_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBX11_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBX11_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES "${CONAN_SYSTEM_LIBS_XTRANS} ${CONAN_FRAMEWORKS_FOUND_XTRANS} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XTRANS_DEPENDENCIES "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XTRANS}" "${CONAN_LIB_DIRS_XTRANS}"
                                  CONAN_PACKAGE_TARGETS_XTRANS "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES}"
                                  "" xtrans)
    set(_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_XTRANS_DEBUG} ${CONAN_FRAMEWORKS_FOUND_XTRANS_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XTRANS_DEBUG}" "${CONAN_LIB_DIRS_XTRANS_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_XTRANS_DEBUG "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_DEBUG}"
                                  "debug" xtrans)
    set(_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_XTRANS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_XTRANS_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XTRANS_RELEASE}" "${CONAN_LIB_DIRS_XTRANS_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_XTRANS_RELEASE "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELEASE}"
                                  "release" xtrans)
    set(_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_XTRANS_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_XTRANS_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XTRANS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_XTRANS_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_XTRANS_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" xtrans)
    set(_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_XTRANS_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_XTRANS_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XTRANS_MINSIZEREL}" "${CONAN_LIB_DIRS_XTRANS_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_XTRANS_MINSIZEREL "${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" xtrans)

    add_library(CONAN_PKG::xtrans INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::xtrans PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_XTRANS} ${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_XTRANS_LIST} ${CONAN_EXE_LINKER_FLAGS_XTRANS_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_XTRANS_RELEASE} ${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_XTRANS_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_XTRANS_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_XTRANS_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_XTRANS_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_XTRANS_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_XTRANS_MINSIZEREL} ${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_XTRANS_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_XTRANS_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_XTRANS_DEBUG} ${_CONAN_PKG_LIBS_XTRANS_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_XTRANS_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_XTRANS_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::xtrans PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_XTRANS}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_XTRANS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_XTRANS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_XTRANS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_XTRANS_DEBUG}>)
    set_property(TARGET CONAN_PKG::xtrans PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_XTRANS}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_XTRANS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_XTRANS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_XTRANS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_XTRANS_DEBUG}>)
    set_property(TARGET CONAN_PKG::xtrans PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_XTRANS_LIST} ${CONAN_CXX_FLAGS_XTRANS_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_XTRANS_RELEASE_LIST} ${CONAN_CXX_FLAGS_XTRANS_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_XTRANS_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_XTRANS_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_XTRANS_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_XTRANS_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_XTRANS_DEBUG_LIST}  ${CONAN_CXX_FLAGS_XTRANS_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXCB} ${CONAN_FRAMEWORKS_FOUND_LIBXCB} CONAN_PKG::xcb-proto CONAN_PKG::util-macros CONAN_PKG::libxau CONAN_PKG::libpthread-stubs CONAN_PKG::libxdmcp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCB}" "${CONAN_LIB_DIRS_LIBXCB}"
                                  CONAN_PACKAGE_TARGETS_LIBXCB "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES}"
                                  "" libxcb)
    set(_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXCB_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXCB_DEBUG} CONAN_PKG::xcb-proto CONAN_PKG::util-macros CONAN_PKG::libxau CONAN_PKG::libpthread-stubs CONAN_PKG::libxdmcp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCB_DEBUG}" "${CONAN_LIB_DIRS_LIBXCB_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXCB_DEBUG "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_DEBUG}"
                                  "debug" libxcb)
    set(_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXCB_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXCB_RELEASE} CONAN_PKG::xcb-proto CONAN_PKG::util-macros CONAN_PKG::libxau CONAN_PKG::libpthread-stubs CONAN_PKG::libxdmcp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCB_RELEASE}" "${CONAN_LIB_DIRS_LIBXCB_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXCB_RELEASE "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELEASE}"
                                  "release" libxcb)
    set(_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXCB_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXCB_RELWITHDEBINFO} CONAN_PKG::xcb-proto CONAN_PKG::util-macros CONAN_PKG::libxau CONAN_PKG::libpthread-stubs CONAN_PKG::libxdmcp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCB_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXCB_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXCB_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxcb)
    set(_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXCB_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXCB_MINSIZEREL} CONAN_PKG::xcb-proto CONAN_PKG::util-macros CONAN_PKG::libxau CONAN_PKG::libpthread-stubs CONAN_PKG::libxdmcp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXCB_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXCB_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXCB_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxcb)

    add_library(CONAN_PKG::libxcb INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxcb PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXCB} ${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXCB_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCB_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXCB_RELEASE} ${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXCB_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCB_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXCB_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXCB_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCB_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXCB_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXCB_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCB_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXCB_DEBUG} ${_CONAN_PKG_LIBS_LIBXCB_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXCB_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXCB_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxcb PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXCB}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXCB_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXCB_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXCB_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXCB_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxcb PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXCB}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXCB_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXCB_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXCB_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXCB_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxcb PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXCB_LIST} ${CONAN_CXX_FLAGS_LIBXCB_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXCB_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXCB_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXCB_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXCB_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXCB_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXCB_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXCB_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXCB_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES "${CONAN_SYSTEM_LIBS_XCB-PROTO} ${CONAN_FRAMEWORKS_FOUND_XCB-PROTO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XCB-PROTO}" "${CONAN_LIB_DIRS_XCB-PROTO}"
                                  CONAN_PACKAGE_TARGETS_XCB-PROTO "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES}"
                                  "" xcb-proto)
    set(_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_XCB-PROTO_DEBUG} ${CONAN_FRAMEWORKS_FOUND_XCB-PROTO_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XCB-PROTO_DEBUG}" "${CONAN_LIB_DIRS_XCB-PROTO_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_XCB-PROTO_DEBUG "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_DEBUG}"
                                  "debug" xcb-proto)
    set(_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_XCB-PROTO_RELEASE} ${CONAN_FRAMEWORKS_FOUND_XCB-PROTO_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XCB-PROTO_RELEASE}" "${CONAN_LIB_DIRS_XCB-PROTO_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_XCB-PROTO_RELEASE "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELEASE}"
                                  "release" xcb-proto)
    set(_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_XCB-PROTO_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_XCB-PROTO_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XCB-PROTO_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_XCB-PROTO_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_XCB-PROTO_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" xcb-proto)
    set(_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_XCB-PROTO_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_XCB-PROTO_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XCB-PROTO_MINSIZEREL}" "${CONAN_LIB_DIRS_XCB-PROTO_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_XCB-PROTO_MINSIZEREL "${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" xcb-proto)

    add_library(CONAN_PKG::xcb-proto INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::xcb-proto PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_XCB-PROTO} ${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_XCB-PROTO_LIST} ${CONAN_EXE_LINKER_FLAGS_XCB-PROTO_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_XCB-PROTO_RELEASE} ${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_XCB-PROTO_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_XCB-PROTO_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_XCB-PROTO_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_XCB-PROTO_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_XCB-PROTO_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_XCB-PROTO_MINSIZEREL} ${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_XCB-PROTO_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_XCB-PROTO_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_XCB-PROTO_DEBUG} ${_CONAN_PKG_LIBS_XCB-PROTO_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_XCB-PROTO_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_XCB-PROTO_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::xcb-proto PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_XCB-PROTO}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_XCB-PROTO_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_XCB-PROTO_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_XCB-PROTO_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_XCB-PROTO_DEBUG}>)
    set_property(TARGET CONAN_PKG::xcb-proto PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_XCB-PROTO}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_XCB-PROTO_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_XCB-PROTO_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_XCB-PROTO_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_XCB-PROTO_DEBUG}>)
    set_property(TARGET CONAN_PKG::xcb-proto PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_XCB-PROTO_LIST} ${CONAN_CXX_FLAGS_XCB-PROTO_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_XCB-PROTO_RELEASE_LIST} ${CONAN_CXX_FLAGS_XCB-PROTO_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_XCB-PROTO_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_XCB-PROTO_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_XCB-PROTO_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_XCB-PROTO_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_XCB-PROTO_DEBUG_LIST}  ${CONAN_CXX_FLAGS_XCB-PROTO_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES "${CONAN_SYSTEM_LIBS_UTIL-MACROS} ${CONAN_FRAMEWORKS_FOUND_UTIL-MACROS} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_UTIL-MACROS}" "${CONAN_LIB_DIRS_UTIL-MACROS}"
                                  CONAN_PACKAGE_TARGETS_UTIL-MACROS "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES}"
                                  "" util-macros)
    set(_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_UTIL-MACROS_DEBUG} ${CONAN_FRAMEWORKS_FOUND_UTIL-MACROS_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_UTIL-MACROS_DEBUG}" "${CONAN_LIB_DIRS_UTIL-MACROS_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_UTIL-MACROS_DEBUG "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_DEBUG}"
                                  "debug" util-macros)
    set(_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_UTIL-MACROS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_UTIL-MACROS_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_UTIL-MACROS_RELEASE}" "${CONAN_LIB_DIRS_UTIL-MACROS_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_UTIL-MACROS_RELEASE "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELEASE}"
                                  "release" util-macros)
    set(_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_UTIL-MACROS_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_UTIL-MACROS_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_UTIL-MACROS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_UTIL-MACROS_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_UTIL-MACROS_RELWITHDEBINFO "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" util-macros)
    set(_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_UTIL-MACROS_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_UTIL-MACROS_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_UTIL-MACROS_MINSIZEREL}" "${CONAN_LIB_DIRS_UTIL-MACROS_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_UTIL-MACROS_MINSIZEREL "${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" util-macros)

    add_library(CONAN_PKG::util-macros INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::util-macros PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_UTIL-MACROS} ${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_UTIL-MACROS_LIST} ${CONAN_EXE_LINKER_FLAGS_UTIL-MACROS_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_UTIL-MACROS_RELEASE} ${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_UTIL-MACROS_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_UTIL-MACROS_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_UTIL-MACROS_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_UTIL-MACROS_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_UTIL-MACROS_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_UTIL-MACROS_MINSIZEREL} ${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_UTIL-MACROS_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_UTIL-MACROS_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_UTIL-MACROS_DEBUG} ${_CONAN_PKG_LIBS_UTIL-MACROS_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_UTIL-MACROS_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_UTIL-MACROS_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::util-macros PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_UTIL-MACROS}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_UTIL-MACROS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_UTIL-MACROS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_UTIL-MACROS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_UTIL-MACROS_DEBUG}>)
    set_property(TARGET CONAN_PKG::util-macros PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_UTIL-MACROS}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_UTIL-MACROS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_UTIL-MACROS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_UTIL-MACROS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_UTIL-MACROS_DEBUG}>)
    set_property(TARGET CONAN_PKG::util-macros PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_UTIL-MACROS_LIST} ${CONAN_CXX_FLAGS_UTIL-MACROS_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_UTIL-MACROS_RELEASE_LIST} ${CONAN_CXX_FLAGS_UTIL-MACROS_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_UTIL-MACROS_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_UTIL-MACROS_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_UTIL-MACROS_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_UTIL-MACROS_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_UTIL-MACROS_DEBUG_LIST}  ${CONAN_CXX_FLAGS_UTIL-MACROS_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXAU} ${CONAN_FRAMEWORKS_FOUND_LIBXAU} CONAN_PKG::xorgproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXAU}" "${CONAN_LIB_DIRS_LIBXAU}"
                                  CONAN_PACKAGE_TARGETS_LIBXAU "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES}"
                                  "" libxau)
    set(_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXAU_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXAU_DEBUG} CONAN_PKG::xorgproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXAU_DEBUG}" "${CONAN_LIB_DIRS_LIBXAU_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXAU_DEBUG "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_DEBUG}"
                                  "debug" libxau)
    set(_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXAU_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXAU_RELEASE} CONAN_PKG::xorgproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXAU_RELEASE}" "${CONAN_LIB_DIRS_LIBXAU_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXAU_RELEASE "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELEASE}"
                                  "release" libxau)
    set(_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXAU_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXAU_RELWITHDEBINFO} CONAN_PKG::xorgproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXAU_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXAU_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXAU_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxau)
    set(_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXAU_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXAU_MINSIZEREL} CONAN_PKG::xorgproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXAU_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXAU_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXAU_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxau)

    add_library(CONAN_PKG::libxau INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxau PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXAU} ${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXAU_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXAU_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXAU_RELEASE} ${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXAU_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXAU_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXAU_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXAU_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXAU_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXAU_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXAU_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXAU_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXAU_DEBUG} ${_CONAN_PKG_LIBS_LIBXAU_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXAU_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXAU_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxau PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXAU}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXAU_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXAU_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXAU_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXAU_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxau PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXAU}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXAU_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXAU_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXAU_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXAU_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxau PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXAU_LIST} ${CONAN_CXX_FLAGS_LIBXAU_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXAU_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXAU_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXAU_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXAU_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXAU_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXAU_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXAU_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXAU_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBPTHREAD-STUBS} ${CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPTHREAD-STUBS}" "${CONAN_LIB_DIRS_LIBPTHREAD-STUBS}"
                                  CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES}"
                                  "" libpthread-stubs)
    set(_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBPTHREAD-STUBS_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEBUG}" "${CONAN_LIB_DIRS_LIBPTHREAD-STUBS_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_DEBUG "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_DEBUG}"
                                  "debug" libpthread-stubs)
    set(_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBPTHREAD-STUBS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPTHREAD-STUBS_RELEASE}" "${CONAN_LIB_DIRS_LIBPTHREAD-STUBS_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_RELEASE "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELEASE}"
                                  "release" libpthread-stubs)
    set(_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBPTHREAD-STUBS_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPTHREAD-STUBS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBPTHREAD-STUBS_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libpthread-stubs)
    set(_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBPTHREAD-STUBS_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBPTHREAD-STUBS_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPTHREAD-STUBS_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBPTHREAD-STUBS_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_MINSIZEREL "${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libpthread-stubs)

    add_library(CONAN_PKG::libpthread-stubs INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libpthread-stubs PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS} ${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBPTHREAD-STUBS_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPTHREAD-STUBS_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_RELEASE} ${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBPTHREAD-STUBS_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPTHREAD-STUBS_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBPTHREAD-STUBS_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPTHREAD-STUBS_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBPTHREAD-STUBS_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPTHREAD-STUBS_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBPTHREAD-STUBS_DEBUG} ${_CONAN_PKG_LIBS_LIBPTHREAD-STUBS_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBPTHREAD-STUBS_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBPTHREAD-STUBS_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libpthread-stubs PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBPTHREAD-STUBS}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBPTHREAD-STUBS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBPTHREAD-STUBS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBPTHREAD-STUBS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBPTHREAD-STUBS_DEBUG}>)
    set_property(TARGET CONAN_PKG::libpthread-stubs PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBPTHREAD-STUBS}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBPTHREAD-STUBS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBPTHREAD-STUBS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBPTHREAD-STUBS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBPTHREAD-STUBS_DEBUG}>)
    set_property(TARGET CONAN_PKG::libpthread-stubs PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBPTHREAD-STUBS_LIST} ${CONAN_CXX_FLAGS_LIBPTHREAD-STUBS_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBPTHREAD-STUBS_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBPTHREAD-STUBS_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBPTHREAD-STUBS_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBPTHREAD-STUBS_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBPTHREAD-STUBS_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBPTHREAD-STUBS_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBPTHREAD-STUBS_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBPTHREAD-STUBS_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBXDMCP} ${CONAN_FRAMEWORKS_FOUND_LIBXDMCP} CONAN_PKG::xproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDMCP}" "${CONAN_LIB_DIRS_LIBXDMCP}"
                                  CONAN_PACKAGE_TARGETS_LIBXDMCP "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES}"
                                  "" libxdmcp)
    set(_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBXDMCP_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBXDMCP_DEBUG} CONAN_PKG::xproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDMCP_DEBUG}" "${CONAN_LIB_DIRS_LIBXDMCP_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBXDMCP_DEBUG "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_DEBUG}"
                                  "debug" libxdmcp)
    set(_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBXDMCP_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBXDMCP_RELEASE} CONAN_PKG::xproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDMCP_RELEASE}" "${CONAN_LIB_DIRS_LIBXDMCP_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBXDMCP_RELEASE "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELEASE}"
                                  "release" libxdmcp)
    set(_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBXDMCP_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBXDMCP_RELWITHDEBINFO} CONAN_PKG::xproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDMCP_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBXDMCP_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBXDMCP_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libxdmcp)
    set(_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBXDMCP_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBXDMCP_MINSIZEREL} CONAN_PKG::xproto")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBXDMCP_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBXDMCP_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBXDMCP_MINSIZEREL "${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libxdmcp)

    add_library(CONAN_PKG::libxdmcp INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libxdmcp PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBXDMCP} ${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_LIBXDMCP_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDMCP_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBXDMCP_RELEASE} ${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_LIBXDMCP_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDMCP_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBXDMCP_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_LIBXDMCP_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDMCP_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBXDMCP_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_LIBXDMCP_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDMCP_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBXDMCP_DEBUG} ${_CONAN_PKG_LIBS_LIBXDMCP_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_LIBXDMCP_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_LIBXDMCP_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::libxdmcp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBXDMCP}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBXDMCP_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBXDMCP_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBXDMCP_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBXDMCP_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxdmcp PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBXDMCP}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBXDMCP_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBXDMCP_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBXDMCP_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBXDMCP_DEBUG}>)
    set_property(TARGET CONAN_PKG::libxdmcp PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBXDMCP_LIST} ${CONAN_CXX_FLAGS_LIBXDMCP_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBXDMCP_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBXDMCP_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBXDMCP_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBXDMCP_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBXDMCP_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBXDMCP_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBXDMCP_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBXDMCP_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES "${CONAN_SYSTEM_LIBS_XORGPROTO} ${CONAN_FRAMEWORKS_FOUND_XORGPROTO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XORGPROTO}" "${CONAN_LIB_DIRS_XORGPROTO}"
                                  CONAN_PACKAGE_TARGETS_XORGPROTO "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES}"
                                  "" xorgproto)
    set(_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_XORGPROTO_DEBUG} ${CONAN_FRAMEWORKS_FOUND_XORGPROTO_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XORGPROTO_DEBUG}" "${CONAN_LIB_DIRS_XORGPROTO_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_XORGPROTO_DEBUG "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_DEBUG}"
                                  "debug" xorgproto)
    set(_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_XORGPROTO_RELEASE} ${CONAN_FRAMEWORKS_FOUND_XORGPROTO_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XORGPROTO_RELEASE}" "${CONAN_LIB_DIRS_XORGPROTO_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_XORGPROTO_RELEASE "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELEASE}"
                                  "release" xorgproto)
    set(_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_XORGPROTO_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_XORGPROTO_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XORGPROTO_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_XORGPROTO_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_XORGPROTO_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" xorgproto)
    set(_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_XORGPROTO_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_XORGPROTO_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XORGPROTO_MINSIZEREL}" "${CONAN_LIB_DIRS_XORGPROTO_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_XORGPROTO_MINSIZEREL "${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" xorgproto)

    add_library(CONAN_PKG::xorgproto INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::xorgproto PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_XORGPROTO} ${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_XORGPROTO_LIST} ${CONAN_EXE_LINKER_FLAGS_XORGPROTO_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_XORGPROTO_RELEASE} ${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_XORGPROTO_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_XORGPROTO_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_XORGPROTO_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_XORGPROTO_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_XORGPROTO_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_XORGPROTO_MINSIZEREL} ${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_XORGPROTO_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_XORGPROTO_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_XORGPROTO_DEBUG} ${_CONAN_PKG_LIBS_XORGPROTO_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_XORGPROTO_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_XORGPROTO_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::xorgproto PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_XORGPROTO}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_XORGPROTO_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_XORGPROTO_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_XORGPROTO_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_XORGPROTO_DEBUG}>)
    set_property(TARGET CONAN_PKG::xorgproto PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_XORGPROTO}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_XORGPROTO_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_XORGPROTO_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_XORGPROTO_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_XORGPROTO_DEBUG}>)
    set_property(TARGET CONAN_PKG::xorgproto PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_XORGPROTO_LIST} ${CONAN_CXX_FLAGS_XORGPROTO_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_XORGPROTO_RELEASE_LIST} ${CONAN_CXX_FLAGS_XORGPROTO_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_XORGPROTO_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_XORGPROTO_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_XORGPROTO_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_XORGPROTO_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_XORGPROTO_DEBUG_LIST}  ${CONAN_CXX_FLAGS_XORGPROTO_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES "${CONAN_SYSTEM_LIBS_XPROTO} ${CONAN_FRAMEWORKS_FOUND_XPROTO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XPROTO_DEPENDENCIES "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XPROTO}" "${CONAN_LIB_DIRS_XPROTO}"
                                  CONAN_PACKAGE_TARGETS_XPROTO "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES}"
                                  "" xproto)
    set(_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_XPROTO_DEBUG} ${CONAN_FRAMEWORKS_FOUND_XPROTO_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XPROTO_DEBUG}" "${CONAN_LIB_DIRS_XPROTO_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_XPROTO_DEBUG "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_DEBUG}"
                                  "debug" xproto)
    set(_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_XPROTO_RELEASE} ${CONAN_FRAMEWORKS_FOUND_XPROTO_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XPROTO_RELEASE}" "${CONAN_LIB_DIRS_XPROTO_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_XPROTO_RELEASE "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELEASE}"
                                  "release" xproto)
    set(_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_XPROTO_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_XPROTO_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XPROTO_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_XPROTO_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_XPROTO_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" xproto)
    set(_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_XPROTO_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_XPROTO_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XPROTO_MINSIZEREL}" "${CONAN_LIB_DIRS_XPROTO_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_XPROTO_MINSIZEREL "${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" xproto)

    add_library(CONAN_PKG::xproto INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::xproto PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_XPROTO} ${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES} ${CONAN_SHARED_LINKER_FLAGS_XPROTO_LIST} ${CONAN_EXE_LINKER_FLAGS_XPROTO_LIST}
                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_XPROTO_RELEASE} ${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELEASE} ${CONAN_SHARED_LINKER_FLAGS_XPROTO_RELEASE_LIST} ${CONAN_EXE_LINKER_FLAGS_XPROTO_RELEASE_LIST}>
                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_XPROTO_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_RELWITHDEBINFO} ${CONAN_SHARED_LINKER_FLAGS_XPROTO_RELWITHDEBINFO_LIST} ${CONAN_EXE_LINKER_FLAGS_XPROTO_RELWITHDEBINFO_LIST}>
                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_XPROTO_MINSIZEREL} ${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_MINSIZEREL} ${CONAN_SHARED_LINKER_FLAGS_XPROTO_MINSIZEREL_LIST} ${CONAN_EXE_LINKER_FLAGS_XPROTO_MINSIZEREL_LIST}>
                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_XPROTO_DEBUG} ${_CONAN_PKG_LIBS_XPROTO_DEPENDENCIES_DEBUG} ${CONAN_SHARED_LINKER_FLAGS_XPROTO_DEBUG_LIST} ${CONAN_EXE_LINKER_FLAGS_XPROTO_DEBUG_LIST}>)
    set_property(TARGET CONAN_PKG::xproto PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_XPROTO}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_XPROTO_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_XPROTO_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_XPROTO_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_XPROTO_DEBUG}>)
    set_property(TARGET CONAN_PKG::xproto PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_XPROTO}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_XPROTO_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_XPROTO_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_XPROTO_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_XPROTO_DEBUG}>)
    set_property(TARGET CONAN_PKG::xproto PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_XPROTO_LIST} ${CONAN_CXX_FLAGS_XPROTO_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_XPROTO_RELEASE_LIST} ${CONAN_CXX_FLAGS_XPROTO_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_XPROTO_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_XPROTO_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_XPROTO_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_XPROTO_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_XPROTO_DEBUG_LIST}  ${CONAN_CXX_FLAGS_XPROTO_DEBUG_LIST}>)

    set(CONAN_TARGETS CONAN_PKG::glfw CONAN_PKG::libxinerama CONAN_PKG::libxcursor CONAN_PKG::libxi CONAN_PKG::mesa CONAN_PKG::libxrandr CONAN_PKG::zlib CONAN_PKG::expat CONAN_PKG::libdrm CONAN_PKG::libelf CONAN_PKG::libunwind CONAN_PKG::libxdamage CONAN_PKG::libxshmfence CONAN_PKG::libxxf86vm CONAN_PKG::libxrender CONAN_PKG::libxext CONAN_PKG::libxfixes CONAN_PKG::libpciaccess CONAN_PKG::xz_utils CONAN_PKG::libx11 CONAN_PKG::xtrans CONAN_PKG::libxcb CONAN_PKG::xcb-proto CONAN_PKG::util-macros CONAN_PKG::libxau CONAN_PKG::libpthread-stubs CONAN_PKG::libxdmcp CONAN_PKG::xorgproto CONAN_PKG::xproto)

endmacro()


macro(conan_basic_setup)
    set(options TARGETS NO_OUTPUT_DIRS SKIP_RPATH KEEP_RPATHS SKIP_STD SKIP_FPIC)
    cmake_parse_arguments(ARGUMENTS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if(CONAN_EXPORTED)
        conan_message(STATUS "Conan: called by CMake conan helper")
    endif()

    if(CONAN_IN_LOCAL_CACHE)
        conan_message(STATUS "Conan: called inside local cache")
    endif()

    if(NOT ARGUMENTS_NO_OUTPUT_DIRS)
        conan_message(STATUS "Conan: Adjusting output directories")
        conan_output_dirs_setup()
    endif()

    if(NOT ARGUMENTS_TARGETS)
        conan_message(STATUS "Conan: Using cmake global configuration")
        conan_global_flags()
    else()
        conan_message(STATUS "Conan: Using cmake targets configuration")
        conan_define_targets()
    endif()

    if(ARGUMENTS_SKIP_RPATH)
        # Change by "DEPRECATION" or "SEND_ERROR" when we are ready
        conan_message(WARNING "Conan: SKIP_RPATH is deprecated, it has been renamed to KEEP_RPATHS")
    endif()

    if(NOT ARGUMENTS_SKIP_RPATH AND NOT ARGUMENTS_KEEP_RPATHS)
        # Parameter has renamed, but we keep the compatibility with old SKIP_RPATH
        conan_set_rpath()
    endif()

    if(NOT ARGUMENTS_SKIP_STD)
        conan_set_std()
    endif()

    if(NOT ARGUMENTS_SKIP_FPIC)
        conan_set_fpic()
    endif()

    conan_check_compiler()
    conan_set_libcxx()
    conan_set_vs_runtime()
    conan_set_find_paths()
    conan_include_build_modules()
    conan_set_find_library_paths()
endmacro()


macro(conan_set_find_paths)
    # CMAKE_MODULE_PATH does not have Debug/Release config, but there are variables
    # CONAN_CMAKE_MODULE_PATH_DEBUG to be used by the consumer
    # CMake can find findXXX.cmake files in the root of packages
    set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

    # Make find_package() to work
    set(CMAKE_PREFIX_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_PREFIX_PATH})

    # Set the find root path (cross build)
    set(CMAKE_FIND_ROOT_PATH ${CONAN_CMAKE_FIND_ROOT_PATH} ${CMAKE_FIND_ROOT_PATH})
    if(CONAN_CMAKE_FIND_ROOT_PATH_MODE_PROGRAM)
        set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ${CONAN_CMAKE_FIND_ROOT_PATH_MODE_PROGRAM})
    endif()
    if(CONAN_CMAKE_FIND_ROOT_PATH_MODE_LIBRARY)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ${CONAN_CMAKE_FIND_ROOT_PATH_MODE_LIBRARY})
    endif()
    if(CONAN_CMAKE_FIND_ROOT_PATH_MODE_INCLUDE)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ${CONAN_CMAKE_FIND_ROOT_PATH_MODE_INCLUDE})
    endif()
endmacro()


macro(conan_set_find_library_paths)
    # CMAKE_INCLUDE_PATH, CMAKE_LIBRARY_PATH does not have Debug/Release config, but there are variables
    # CONAN_INCLUDE_DIRS_DEBUG/RELEASE CONAN_LIB_DIRS_DEBUG/RELEASE to be used by the consumer
    # For find_library
    set(CMAKE_INCLUDE_PATH ${CONAN_INCLUDE_DIRS} ${CMAKE_INCLUDE_PATH})
    set(CMAKE_LIBRARY_PATH ${CONAN_LIB_DIRS} ${CMAKE_LIBRARY_PATH})
endmacro()


macro(conan_set_vs_runtime)
    if(CONAN_LINK_RUNTIME)
        conan_get_policy(CMP0091 policy_0091)
        if(policy_0091 STREQUAL "NEW")
            if(CONAN_LINK_RUNTIME MATCHES "MTd")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
            elseif(CONAN_LINK_RUNTIME MATCHES "MDd")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
            elseif(CONAN_LINK_RUNTIME MATCHES "MT")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
            elseif(CONAN_LINK_RUNTIME MATCHES "MD")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
            endif()
        else()
            foreach(flag CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE
                         CMAKE_C_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_RELWITHDEBINFO
                         CMAKE_C_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_MINSIZEREL)
                if(DEFINED ${flag})
                    string(REPLACE "/MD" ${CONAN_LINK_RUNTIME} ${flag} "${${flag}}")
                endif()
            endforeach()
            foreach(flag CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG)
                if(DEFINED ${flag})
                    string(REPLACE "/MDd" ${CONAN_LINK_RUNTIME} ${flag} "${${flag}}")
                endif()
            endforeach()
        endif()
    endif()
endmacro()


macro(conan_flags_setup)
    # Macro maintained for backwards compatibility
    conan_set_find_library_paths()
    conan_global_flags()
    conan_set_rpath()
    conan_set_vs_runtime()
    conan_set_libcxx()
endmacro()


function(conan_message MESSAGE_OUTPUT)
    if(NOT CONAN_CMAKE_SILENT_OUTPUT)
        message(${ARGV${0}})
    endif()
endfunction()


function(conan_get_policy policy_id policy)
    if(POLICY "${policy_id}")
        cmake_policy(GET "${policy_id}" _policy)
        set(policy "${_policy}" PARENT_SCOPE)
    else()
        set(policy "" PARENT_SCOPE) 
    endif()
endfunction()


function(conan_find_libraries_abs_path libraries package_libdir libraries_abs_path)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAME ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${CONAN_FOUND_LIBRARY})
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${_LIBRARY_NAME})
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()
    set(${libraries_abs_path} ${CONAN_FULLPATH_LIBS} PARENT_SCOPE)
endfunction()


function(conan_package_library_targets libraries package_libdir libraries_abs_path deps build_type package_name)
    unset(_CONAN_ACTUAL_TARGETS CACHE)
    unset(_CONAN_FOUND_SYSTEM_LIBS CACHE)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAME ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            set(_LIB_NAME CONAN_LIB::${package_name}_${_LIBRARY_NAME}${build_type})
            add_library(${_LIB_NAME} UNKNOWN IMPORTED)
            set_target_properties(${_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CONAN_FOUND_LIBRARY})
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${_LIB_NAME})
            set(_CONAN_ACTUAL_TARGETS ${_CONAN_ACTUAL_TARGETS} ${_LIB_NAME})
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${_LIBRARY_NAME})
            set(_CONAN_FOUND_SYSTEM_LIBS "${_CONAN_FOUND_SYSTEM_LIBS};${_LIBRARY_NAME}")
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()

    # Add all dependencies to all targets
    string(REPLACE " " ";" deps_list "${deps}")
    foreach(_CONAN_ACTUAL_TARGET ${_CONAN_ACTUAL_TARGETS})
        set_property(TARGET ${_CONAN_ACTUAL_TARGET} PROPERTY INTERFACE_LINK_LIBRARIES "${_CONAN_FOUND_SYSTEM_LIBS};${deps_list}")
    endforeach()

    set(${libraries_abs_path} ${CONAN_FULLPATH_LIBS} PARENT_SCOPE)
endfunction()


macro(conan_set_libcxx)
    if(DEFINED CONAN_LIBCXX)
        conan_message(STATUS "Conan: C++ stdlib: ${CONAN_LIBCXX}")
        if(CONAN_COMPILER STREQUAL "clang" OR CONAN_COMPILER STREQUAL "apple-clang")
            if(CONAN_LIBCXX STREQUAL "libstdc++" OR CONAN_LIBCXX STREQUAL "libstdc++11" )
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
            elseif(CONAN_LIBCXX STREQUAL "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
            endif()
        endif()
        if(CONAN_COMPILER STREQUAL "sun-cc")
            if(CONAN_LIBCXX STREQUAL "libCstd")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=Cstd")
            elseif(CONAN_LIBCXX STREQUAL "libstdcxx")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=stdcxx4")
            elseif(CONAN_LIBCXX STREQUAL "libstlport")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=stlport4")
            elseif(CONAN_LIBCXX STREQUAL "libstdc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=stdcpp")
            endif()
        endif()
        if(CONAN_LIBCXX STREQUAL "libstdc++11")
            add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
        elseif(CONAN_LIBCXX STREQUAL "libstdc++")
            add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
        endif()
    endif()
endmacro()


macro(conan_set_std)
    conan_message(STATUS "Conan: Adjusting language standard")
    # Do not warn "Manually-specified variables were not used by the project"
    set(ignorevar "${CONAN_STD_CXX_FLAG}${CONAN_CMAKE_CXX_STANDARD}${CONAN_CMAKE_CXX_EXTENSIONS}")
    if (CMAKE_VERSION VERSION_LESS "3.1" OR
        (CMAKE_VERSION VERSION_LESS "3.12" AND ("${CONAN_CMAKE_CXX_STANDARD}" STREQUAL "20" OR "${CONAN_CMAKE_CXX_STANDARD}" STREQUAL "gnu20")))
        if(CONAN_STD_CXX_FLAG)
            conan_message(STATUS "Conan setting CXX_FLAGS flags: ${CONAN_STD_CXX_FLAG}")
            set(CMAKE_CXX_FLAGS "${CONAN_STD_CXX_FLAG} ${CMAKE_CXX_FLAGS}")
        endif()
    else()
        if(CONAN_CMAKE_CXX_STANDARD)
            conan_message(STATUS "Conan setting CPP STANDARD: ${CONAN_CMAKE_CXX_STANDARD} WITH EXTENSIONS ${CONAN_CMAKE_CXX_EXTENSIONS}")
            set(CMAKE_CXX_STANDARD ${CONAN_CMAKE_CXX_STANDARD})
            set(CMAKE_CXX_EXTENSIONS ${CONAN_CMAKE_CXX_EXTENSIONS})
        endif()
    endif()
endmacro()


macro(conan_set_rpath)
    conan_message(STATUS "Conan: Adjusting default RPATHs Conan policies")
    if(APPLE)
        # https://cmake.org/Wiki/CMake_RPATH_handling
        # CONAN GUIDE: All generated libraries should have the id and dependencies to other
        # dylibs without path, just the name, EX:
        # libMyLib1.dylib:
        #     libMyLib1.dylib (compatibility version 0.0.0, current version 0.0.0)
        #     libMyLib0.dylib (compatibility version 0.0.0, current version 0.0.0)
        #     /usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 120.0.0)
        #     /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1197.1.1)
        set(CMAKE_SKIP_RPATH 1)  # AVOID RPATH FOR *.dylib, ALL LIBS BETWEEN THEM AND THE EXE
                                 # SHOULD BE ON THE LINKER RESOLVER PATH (./ IS ONE OF THEM)
        # Policy CMP0068
        # We want the old behavior, in CMake >= 3.9 CMAKE_SKIP_RPATH won't affect the install_name in OSX
        set(CMAKE_INSTALL_NAME_DIR "")
    endif()
endmacro()


macro(conan_set_fpic)
    if(DEFINED CONAN_CMAKE_POSITION_INDEPENDENT_CODE)
        conan_message(STATUS "Conan: Adjusting fPIC flag (${CONAN_CMAKE_POSITION_INDEPENDENT_CODE})")
        set(CMAKE_POSITION_INDEPENDENT_CODE ${CONAN_CMAKE_POSITION_INDEPENDENT_CODE})
    endif()
endmacro()


macro(conan_output_dirs_setup)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endmacro()


macro(conan_split_version VERSION_STRING MAJOR MINOR)
    #make a list from the version string
    string(REPLACE "." ";" VERSION_LIST "${VERSION_STRING}")

    #write output values
    list(LENGTH VERSION_LIST _version_len)
    list(GET VERSION_LIST 0 ${MAJOR})
    if(${_version_len} GREATER 1)
        list(GET VERSION_LIST 1 ${MINOR})
    endif()
endmacro()


macro(conan_error_compiler_version)
    message(FATAL_ERROR "Detected a mismatch for the compiler version between your conan profile settings and CMake: \n"
                        "Compiler version specified in your conan profile: ${CONAN_COMPILER_VERSION}\n"
                        "Compiler version detected in CMake: ${VERSION_MAJOR}.${VERSION_MINOR}\n"
                        "Please check your conan profile settings (conan profile show [default|your_profile_name])"
           )
endmacro()

set(_CONAN_CURRENT_DIR ${CMAKE_CURRENT_LIST_DIR})

function(conan_get_compiler CONAN_INFO_COMPILER CONAN_INFO_COMPILER_VERSION)
    conan_message(STATUS "Current conanbuildinfo.cmake directory: " ${_CONAN_CURRENT_DIR})
    if(NOT EXISTS ${_CONAN_CURRENT_DIR}/conaninfo.txt)
        conan_message(STATUS "WARN: conaninfo.txt not found")
        return()
    endif()

    file (READ "${_CONAN_CURRENT_DIR}/conaninfo.txt" CONANINFO)

    string(REGEX MATCH "compiler=([-A-Za-z0-9_ ]+)" _MATCHED ${CONANINFO})
    if(DEFINED CMAKE_MATCH_1)
        string(STRIP "${CMAKE_MATCH_1}" _CONAN_INFO_COMPILER)
        set(${CONAN_INFO_COMPILER} ${_CONAN_INFO_COMPILER} PARENT_SCOPE)
    endif()

    string(REGEX MATCH "compiler.version=([-A-Za-z0-9_.]+)" _MATCHED ${CONANINFO})
    if(DEFINED CMAKE_MATCH_1)
        string(STRIP "${CMAKE_MATCH_1}" _CONAN_INFO_COMPILER_VERSION)
        set(${CONAN_INFO_COMPILER_VERSION} ${_CONAN_INFO_COMPILER_VERSION} PARENT_SCOPE)
    endif()
endfunction()


function(check_compiler_version)
    conan_split_version(${CMAKE_CXX_COMPILER_VERSION} VERSION_MAJOR VERSION_MINOR)
    if(DEFINED CONAN_SETTINGS_COMPILER_TOOLSET)
       conan_message(STATUS "Conan: Skipping compiler check: Declared 'compiler.toolset'")
       return()
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        # MSVC_VERSION is defined since 2.8.2 at least
        # https://cmake.org/cmake/help/v2.8.2/cmake.html#variable:MSVC_VERSION
        # https://cmake.org/cmake/help/v3.14/variable/MSVC_VERSION.html
        if(
            # 1920-1929 = VS 16.0 (v142 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "16" AND NOT((MSVC_VERSION GREATER 1919) AND (MSVC_VERSION LESS 1930))) OR
            # 1910-1919 = VS 15.0 (v141 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "15" AND NOT((MSVC_VERSION GREATER 1909) AND (MSVC_VERSION LESS 1920))) OR
            # 1900      = VS 14.0 (v140 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "14" AND NOT(MSVC_VERSION EQUAL 1900)) OR
            # 1800      = VS 12.0 (v120 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "12" AND NOT VERSION_MAJOR STREQUAL "18") OR
            # 1700      = VS 11.0 (v110 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "11" AND NOT VERSION_MAJOR STREQUAL "17") OR
            # 1600      = VS 10.0 (v100 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "10" AND NOT VERSION_MAJOR STREQUAL "16") OR
            # 1500      = VS  9.0 (v90 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "9" AND NOT VERSION_MAJOR STREQUAL "15") OR
            # 1400      = VS  8.0 (v80 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "8" AND NOT VERSION_MAJOR STREQUAL "14") OR
            # 1310      = VS  7.1, 1300      = VS  7.0
            (CONAN_COMPILER_VERSION STREQUAL "7" AND NOT VERSION_MAJOR STREQUAL "13") OR
            # 1200      = VS  6.0
            (CONAN_COMPILER_VERSION STREQUAL "6" AND NOT VERSION_MAJOR STREQUAL "12") )
            conan_error_compiler_version()
        endif()
    elseif(CONAN_COMPILER STREQUAL "gcc")
        set(_CHECK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
        if(NOT ${CONAN_COMPILER_VERSION} VERSION_LESS 5.0)
            conan_message(STATUS "Conan: Compiler GCC>=5, checking major version ${CONAN_COMPILER_VERSION}")
            conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
            if("${CONAN_COMPILER_MINOR}" STREQUAL "")
                set(_CHECK_VERSION ${VERSION_MAJOR})
            endif()
        endif()
        conan_message(STATUS "Conan: Checking correct version: ${_CHECK_VERSION}")
        if(NOT ${_CHECK_VERSION} VERSION_EQUAL CONAN_COMPILER_VERSION)
            conan_error_compiler_version()
        endif()
    elseif(CONAN_COMPILER STREQUAL "clang")
        set(_CHECK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
        if(NOT ${CONAN_COMPILER_VERSION} VERSION_LESS 8.0)
            conan_message(STATUS "Conan: Compiler Clang>=8, checking major version ${CONAN_COMPILER_VERSION}")
            conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
            if("${CONAN_COMPILER_MINOR}" STREQUAL "")
                set(_CHECK_VERSION ${VERSION_MAJOR})
            endif()
        endif()
        conan_message(STATUS "Conan: Checking correct version: ${_CHECK_VERSION}")
        if(NOT ${_CHECK_VERSION} VERSION_EQUAL CONAN_COMPILER_VERSION)
            conan_error_compiler_version()
        endif()
    elseif(CONAN_COMPILER STREQUAL "apple-clang" OR CONAN_COMPILER STREQUAL "sun-cc")
        conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
        if(NOT ${VERSION_MAJOR}.${VERSION_MINOR} VERSION_EQUAL ${CONAN_COMPILER_MAJOR}.${CONAN_COMPILER_MINOR})
           conan_error_compiler_version()
        endif()
    else()
        conan_message(STATUS "WARN: Unknown compiler '${CONAN_COMPILER}', skipping the version check...")
    endif()
endfunction()


function(conan_check_compiler)
    if(CONAN_DISABLE_CHECK_COMPILER)
        conan_message(STATUS "WARN: Disabled conan compiler checks")
        return()
    endif()
    if(NOT DEFINED CMAKE_CXX_COMPILER_ID)
        if(DEFINED CMAKE_C_COMPILER_ID)
            conan_message(STATUS "This project seems to be plain C, using '${CMAKE_C_COMPILER_ID}' compiler")
            set(CMAKE_CXX_COMPILER_ID ${CMAKE_C_COMPILER_ID})
            set(CMAKE_CXX_COMPILER_VERSION ${CMAKE_C_COMPILER_VERSION})
        else()
            message(FATAL_ERROR "This project seems to be plain C, but no compiler defined")
        endif()
    endif()
    if(NOT CMAKE_CXX_COMPILER_ID AND NOT CMAKE_C_COMPILER_ID)
        # This use case happens when compiler is not identified by CMake, but the compilers are there and work
        conan_message(STATUS "*** WARN: CMake was not able to identify a C or C++ compiler ***")
        conan_message(STATUS "*** WARN: Disabling compiler checks. Please make sure your settings match your environment ***")
        return()
    endif()
    if(NOT DEFINED CONAN_COMPILER)
        conan_get_compiler(CONAN_COMPILER CONAN_COMPILER_VERSION)
        if(NOT DEFINED CONAN_COMPILER)
            conan_message(STATUS "WARN: CONAN_COMPILER variable not set, please make sure yourself that "
                          "your compiler and version matches your declared settings")
            return()
        endif()
    endif()

    if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL ${CMAKE_SYSTEM_NAME})
        set(CROSS_BUILDING 1)
    endif()

    # If using VS, verify toolset
    if (CONAN_COMPILER STREQUAL "Visual Studio")
        if (CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "LLVM" OR
            CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "clang")
            set(EXPECTED_CMAKE_CXX_COMPILER_ID "Clang")
        elseif (CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "Intel")
            set(EXPECTED_CMAKE_CXX_COMPILER_ID "Intel")
        else()
            set(EXPECTED_CMAKE_CXX_COMPILER_ID "MSVC")
        endif()

        if (NOT CMAKE_CXX_COMPILER_ID MATCHES ${EXPECTED_CMAKE_CXX_COMPILER_ID})
            message(FATAL_ERROR "Incorrect '${CONAN_COMPILER}'. Toolset specifies compiler as '${EXPECTED_CMAKE_CXX_COMPILER_ID}' "
                                "but CMake detected '${CMAKE_CXX_COMPILER_ID}'")
        endif()

    # Avoid checks when cross compiling, apple-clang crashes because its APPLE but not apple-clang
    # Actually CMake is detecting "clang" when you are using apple-clang, only if CMP0025 is set to NEW will detect apple-clang
    elseif((CONAN_COMPILER STREQUAL "gcc" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR
        (CONAN_COMPILER STREQUAL "apple-clang" AND NOT CROSS_BUILDING AND (NOT APPLE OR NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")) OR
        (CONAN_COMPILER STREQUAL "clang" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR
        (CONAN_COMPILER STREQUAL "sun-cc" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "SunPro") )
        message(FATAL_ERROR "Incorrect '${CONAN_COMPILER}', is not the one detected by CMake: '${CMAKE_CXX_COMPILER_ID}'")
    endif()


    if(NOT DEFINED CONAN_COMPILER_VERSION)
        conan_message(STATUS "WARN: CONAN_COMPILER_VERSION variable not set, please make sure yourself "
                             "that your compiler version matches your declared settings")
        return()
    endif()
    check_compiler_version()
endfunction()


macro(conan_set_flags build_type)
    set(CMAKE_CXX_FLAGS${build_type} "${CMAKE_CXX_FLAGS${build_type}} ${CONAN_CXX_FLAGS${build_type}}")
    set(CMAKE_C_FLAGS${build_type} "${CMAKE_C_FLAGS${build_type}} ${CONAN_C_FLAGS${build_type}}")
    set(CMAKE_SHARED_LINKER_FLAGS${build_type} "${CMAKE_SHARED_LINKER_FLAGS${build_type}} ${CONAN_SHARED_LINKER_FLAGS${build_type}}")
    set(CMAKE_EXE_LINKER_FLAGS${build_type} "${CMAKE_EXE_LINKER_FLAGS${build_type}} ${CONAN_EXE_LINKER_FLAGS${build_type}}")
endmacro()


macro(conan_global_flags)
    if(CONAN_SYSTEM_INCLUDES)
        include_directories(SYSTEM ${CONAN_INCLUDE_DIRS}
                                   "$<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_RELEASE}>"
                                   "$<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_RELWITHDEBINFO}>"
                                   "$<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_MINSIZEREL}>"
                                   "$<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_DEBUG}>")
    else()
        include_directories(${CONAN_INCLUDE_DIRS}
                            "$<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_RELEASE}>"
                            "$<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_RELWITHDEBINFO}>"
                            "$<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_MINSIZEREL}>"
                            "$<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_DEBUG}>")
    endif()

    link_directories(${CONAN_LIB_DIRS})

    conan_find_libraries_abs_path("${CONAN_LIBS_DEBUG}" "${CONAN_LIB_DIRS_DEBUG}"
                                  CONAN_LIBS_DEBUG)
    conan_find_libraries_abs_path("${CONAN_LIBS_RELEASE}" "${CONAN_LIB_DIRS_RELEASE}"
                                  CONAN_LIBS_RELEASE)
    conan_find_libraries_abs_path("${CONAN_LIBS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_RELWITHDEBINFO}"
                                  CONAN_LIBS_RELWITHDEBINFO)
    conan_find_libraries_abs_path("${CONAN_LIBS_MINSIZEREL}" "${CONAN_LIB_DIRS_MINSIZEREL}"
                                  CONAN_LIBS_MINSIZEREL)

    add_compile_options(${CONAN_DEFINES}
                        "$<$<CONFIG:Debug>:${CONAN_DEFINES_DEBUG}>"
                        "$<$<CONFIG:Release>:${CONAN_DEFINES_RELEASE}>"
                        "$<$<CONFIG:RelWithDebInfo>:${CONAN_DEFINES_RELWITHDEBINFO}>"
                        "$<$<CONFIG:MinSizeRel>:${CONAN_DEFINES_MINSIZEREL}>")

    conan_set_flags("")
    conan_set_flags("_RELEASE")
    conan_set_flags("_DEBUG")

endmacro()


macro(conan_target_link_libraries target)
    if(CONAN_TARGETS)
        target_link_libraries(${target} ${CONAN_TARGETS})
    else()
        target_link_libraries(${target} ${CONAN_LIBS})
        foreach(_LIB ${CONAN_LIBS_RELEASE})
            target_link_libraries(${target} optimized ${_LIB})
        endforeach()
        foreach(_LIB ${CONAN_LIBS_DEBUG})
            target_link_libraries(${target} debug ${_LIB})
        endforeach()
    endif()
endmacro()


macro(conan_include_build_modules)
    if(CMAKE_BUILD_TYPE)
        if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_DEBUG} ${CONAN_BUILD_MODULES_PATHS})
        elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_RELEASE} ${CONAN_BUILD_MODULES_PATHS})
        elseif(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_RELWITHDEBINFO} ${CONAN_BUILD_MODULES_PATHS})
        elseif(${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_MINSIZEREL} ${CONAN_BUILD_MODULES_PATHS})
        endif()
    endif()

    foreach(_BUILD_MODULE_PATH ${CONAN_BUILD_MODULES_PATHS})
        include(${_BUILD_MODULE_PATH})
    endforeach()
endmacro()


### Definition of user declared vars (user_info) ###

