//
// Created by stiven on 12/14/20.
//

#include <string_view>
#include "window.h"
#include "utils/utils.hpp"
#include <GLFW/glfw3.h>

namespace mountain {

    void errorGLFW([[maybe_unused]] int error, const char *msg) {
        utils::printError(msg);
    }

    Window::Window(std::string_view title, unsigned int width, unsigned int height) :
            _width(width),
            _height(height),
            _title(title) {
        glfwSetErrorCallback(errorGLFW);
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(_width, _height, title.data(), nullptr, nullptr);
        if (!_window) {
            utils::printFatalError("unable to Create window");
        }
    }

    std::vector<const char *> Window::get_instance_extension() const {
        uint32_t glfwExtensionCount = 0;
        const char **required_extensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        return std::vector(required_extensions, required_extensions + glfwExtensionCount);
    }

    Window::~Window() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    GLFWwindow *Window::get_window() const {
        return _window;
    }
    VkResult create_window_surface(VkInstance instance,
                                   Window const &handle,
                                   const VkAllocationCallbacks *allocator,
                                   VkSurfaceKHR *surface) {
        return glfwCreateWindowSurface(instance,
                                       handle.get_window(), allocator, surface);

    }
}