//
// Created by stiven on 12/14/20.
//

#ifndef SANDBOX_GLFWWINDOW_H
#define SANDBOX_GLFWWINDOW_H
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <string_view>
#include <vector>
struct Window {
    Window(std::string_view title, unsigned width, unsigned height);
    std::vector<const char *> get_instance_extension() const;
    GLFWwindow * get_window() const;
    ~Window();
private:
    GLFWwindow* _window;
    unsigned _width, _height;

};

inline VkResult create_window_surface(VkInstance instance,
                                      Window const& handle,
                               const VkAllocationCallbacks* allocator,
                               VkSurfaceKHR* surface){
    return glfwCreateWindowSurface(instance,
                                   handle.get_window(), allocator, surface);

}

#endif //SANDBOX_GLFWWINDOW_H
