//
// Created by stiven on 12/14/20.
//

#ifndef MOUNTAIN_API_GLFWWINDOW_H
#define MOUNTAIN_API_GLFWWINDOW_H
#include <vulkan/vulkan.h>
#include <string_view>
#include <string>
#include <vector>
struct GLFWwindow;
namespace mountain {

    /**
     * Window Wrapper around GLFW
     */
    struct Window {
        /**
         * Window ctor
         * @param title: Window title
         * @param width: width of the window
         * @param height: height of the window
         */
        Window(std::string_view title, unsigned width, unsigned height);

        /**
         * @return vector of supported extension by this window
         */
        std::vector<const char *> get_instance_extension() const;

        GLFWwindow *get_window() const;

        std::string_view get_title() const { return _title; }

        ~Window();

    private:
        GLFWwindow *_window;
        unsigned _width, _height;
        std::string _title;
    };
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    VkResult create_window_surface(VkInstance instance,
                                          Window const &handle,
                                          const VkAllocationCallbacks *allocator,
                                          VkSurfaceKHR *surface);

#endif
}
#endif //MOUNTAIN_API_GLFWWINDOW_H
