Getting started
===============

Set Up your project
-------------------
Along this tutorial, I will assume that you use CMake to set up your project.

Build source inside your project
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
All you have to do is to copy the `Mountain-API` directory into your project directory then

.. code-block:: cmake

    add_subdirectory(Mountain-API)
    target_compile_features(<your_target> PRIVATE cxx_std_20)
    target_link_libraries(<your_target> PRIVATE Mountain::API)

That's all you have to do to use Mountain-API

.. Use FindPackage
^^^^^^^^^^^^^

First triangle
-----------------
Let's start with the "Hello World" of 3D Graphics, and render a triangle.

.. image:: image/triangle_getting_started.png

Create Window
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
First we have to create a window to contain our vulkan context

.. code-block:: cpp

    #include "mountain/context.h"
    #include <vector>
    int main(){
            std::vector<const char*> const devices_extension{
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        auto constexpr width = 1366;
        auto constexpr height = 768;
        mountain::Window window("First Triangle", width, height);
        using namespace std::chrono_literals;
        while (!glfwWindowShouldClose(window.get_window())) { //to keep window open
            glfwPollEvents();
            std::this_thread::sleep_for(17ms);
        }
    }



Create Vulkan context
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Now that we have a window let's add a vulkan context

.. code-block:: cpp

    #include "mountain/context.h"
    #include <vector>
    int main(){
        std::vector<const char*> const devices_extension{
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        auto constexpr width = 1366;
        auto constexpr height = 768;
        mountain::Window window("First Triangle", width, height);
        mountain::Context const context{window,
                                        devices_extension};
        using namespace std::chrono_literals;
        while (!glfwWindowShouldClose(window.get_window())) {
            glfwPollEvents();
            std::this_thread::sleep_for(17ms);
        }
    }




