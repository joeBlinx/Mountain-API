Getting started
===============

Set Up your project
-------------------
Along this tutorial, I will assume that you use CMake to set up your project. I will also use GLFW for handling window

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
        mountain::Window const window("First Triangle", width, height);
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
        mountain::Window const window("First Triangle", width, height);
        mountain::Context const context{window,
                                        devices_extension};
        using namespace std::chrono_literals;
        while (!glfwWindowShouldClose(window.get_window())) {
            glfwPollEvents();
            std::this_thread::sleep_for(17ms);
        }
    }

With this little amount of code, we have a window that shown and a vulkan context.
Now we should be able to add some Vulkan stuff.
Since you are a bit familiar with vulkan, if not see this `tutorial <https://vulkan-tutorial.com/>`_, you know that we need some stuff to be able to draw our triangle. With Mountain-API, we'll need a renderpass, a swap chain, a graphics pipeline and command buffers objects. Those four object are part of the Mountain-API and hide a lot a vulkan stuff but you still have some flexibility to choose some options.
First we have to create our render pass (for now, Mountain-API only one subpass is supported).

.. code-block:: cpp

    ...
    using mountain::subpass_attachment;
    mountain::RenderPass const render_pass{
                                context,
                                mountain::SubPass{subpass_attachment::COLOR}
        };
    using namespace std::chrono_literals;
    ...

The ``using`` declaration is too avoid typing ``mountain::subpass_attachment::COLOR`` because it's a bit long. For creating our render pass, we first pass our context. Since Vulkan in agnostic-API, all of Mountain-API classes will require the context before use.
The second parameter is a ``mountain::SubPass`` where we pass which sor of attachment we want. For now we only want ``COLOR`` so that's what we pass. But we can pass ``DEPTH`` or ``STENCIL`` or both in the second parameter of ``mountain::SubPass``.

The second object we need is the swap chain

.. code-block:: cpp

    ...
    //Renderpass...
    mountain::SwapChain const swap_chain{
            context,
            render_pass,
            width,
            height
    };
    ...

There is no big deal with that, the swap chain need the context, the render pass, the width and the height of the image we want to render.
Let's continue with something more interesting

