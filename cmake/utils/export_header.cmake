

include(GenerateExportHeader)

generate_export_header(MountainAPI)
add_library(MountainExportFile INTERFACE)
add_library(Mountain::ExportFile ALIAS MountainExportFile)


target_include_directories(MountainExportFile INTERFACE ${CMAKE_BINARY_DIR})

add_library(MountainExportDefinition INTERFACE)
add_library(Mountain::ExportDefinition ALIAS MountainExportDefinition)
target_compile_definitions(MountainExportDefinition INTERFACE MountainAPI_EXPORTS)
