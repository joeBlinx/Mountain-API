cmake_minimum_required(VERSION 3.12)
project(sandBox)

set(CMAKE_CXX_STANDARD 17)
find_package(Vulkan)

add_definitions(-DGLFW_INCLUDE_VULKAN)
add_executable(sandBox main.cpp initVulkan.cpp initVulkan.hpp log.cpp log.hpp)
target_link_libraries(sandBox vulkan
		glfw3 Xcursor -lX11 -lXxf86vm -lXrandr
		-lpthread -lXi dl -lXi -lXinerama
		utils)