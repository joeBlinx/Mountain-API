//
// Created by stiven on 12/14/20.
//

#include <vector>
#include "window.h"
namespace mountain {

    Window::Window(std::string_view title, unsigned int width, unsigned int height) :
            _width(width),
            _height(height),
            _title(title) {
        SDL_Init(SDL_INIT_EVERYTHING);
        _window = SDL_CreateWindow(title.data(),
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   _width,
                                   _height,
                                   SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);

    }

    std::vector<const char *> Window::get_instance_extension() const {
        unsigned int extensionCount = 0;
        SDL_Vulkan_GetInstanceExtensions(_window, &extensionCount, nullptr);
        std::vector<const char *> extensionNames(extensionCount);
        SDL_Vulkan_GetInstanceExtensions(_window, &extensionCount, extensionNames.data());
        return extensionNames;
    }

    SDL_Window *Window::get_window() const {
        return _window;
    }

    Window::~Window() {
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }
}