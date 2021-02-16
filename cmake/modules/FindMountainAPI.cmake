find_library(
        _mountainapi_bin
        NAME MountainAPI
        PATHS ${CMAKE_CURRENT_LIST_DIR}/bin
)

add_library(MountainAPI SHARED IMPORTED GLOBAL)
add_library(Mountain::API ALIAS MountainAPI)

# some header need C++20 features to be build, this value can be overridden by the user
target_compile_features(MountainAPI INTERFACE cxx_std_20)
target_include_directories(MountainAPI INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

set_target_properties(MountainAPI PROPERTIES
        IMPORTED_LOCATION ${_mountainapi_bin}
        )

