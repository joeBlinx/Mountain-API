cmake_minimum_required(VERSION 3.12)
project(sandBox)

set(CMAKE_CXX_STANDARD 17)
find_package(Vulkan)
#find_package(GLFW)

add_definitions(-DGLFW_INCLUDE_VULKAN)

if(UNIX)

target_link_libraries(sandBox vulkan
		glfw3 Xcursor -lX11 -lXxf86vm -lXrandr
		-lpthread -lXi dl -lXi -lXinerama
		utils)
else()
	include_directories("./")
	include_directories(BEFORE_SYSTEM "../lib/include")
	include_directories(BEFORE_SYSTEM ${Vulkan_INCLUDE_DIRS} )

	link_directories("../lib/bin")
	link_directories(${Vulkan_LIBRARY} )
	message(${Vulkan_LIBRARY}  )

endif()


add_executable(sandBox main.cpp 
						initVulkan.cpp initVulkan.hpp 
						log.cpp log.hpp
						utils.hpp
						sandbox_useful/basicInit.hpp
						sandbox_useful/basicInit.cpp)

						

if(UNIX)

target_link_libraries(sandBox vulkan
		glfw3 Xcursor -lX11 -lXxf86vm -lXrandr
		-lpthread -lXi dl -lXi -lXinerama
		utils)
else()
	target_link_libraries(sandBox glfw3 ${Vulkan_LIBRARY})
endif()