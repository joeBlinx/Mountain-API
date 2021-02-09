//
// Created by stiven on 12/14/20.
//

#ifndef MOUNTAIN_API_SDL2WINDOW_H
#define MOUNTAIN_API_SDL2WINDOW_H
#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>
#include <string_view>
#include <extension.h>
#include <SDL_vulkan.h>
#include <string>
namespace mountain {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    struct Window {
        Window(std::string_view title, unsigned width, unsigned height);

        std::vector<const char *> get_instance_extension() const;

        SDL_Window *get_window() const;

        std::string_view get_title() const { return _title; }

        ~Window();

    private:
        SDL_Window *_window;
        unsigned _width, _height;
        std::string _title;
    };

    inline VkResult create_window_surface(VkInstance instance,
                                          Window const &handle,
                                          const VkAllocationCallbacks *,
                                          VkSurfaceKHR *surface) {
        auto result = SDL_Vulkan_CreateSurface(handle.get_window(), instance, surface);

        return result ? VK_SUCCESS : VK_ERROR_UNKNOWN;

    }
#endif
}
#endif //MOUNTAIN_API_SDL2WINDOW_H
