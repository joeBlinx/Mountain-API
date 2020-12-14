//
// Created by stiven on 12/14/20.
//

#ifndef SANDBOX_WINDOW_H
#define SANDBOX_WINDOW_H
#ifdef USE_GLFW
#include "glfw/window.h"
#elif USE_SDL2
#include "sdl2/window.h"
#else
#error "No window managment specified"
#endif


#endif //SANDBOX_WINDOW_H
