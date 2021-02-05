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

    #include <mountain/renderpass/renderPass.h>
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

    #include <mountain/swapChain.h>
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
Let's continue with something more interesting.
We will now create the Graphics Pipeline. We will talk about vertex and fragment shaders and we will create our first ``vertex buffer``.
The Graphics pipeline object neded 4 things, the ``vulkan context``, the ``swap chain``, the ``render pass``, an array of ``mountain::shader`` and an array of ``vertex buffers``.
Let's create our two shaders files. Call the vertex shader ``triangle.vert``
**Vertex shader**

.. code-block:: glsl

    #version 450
    #extension GL_ARB_separate_shader_objects : enable
    layout(location = 0) in vec2 pos;
    layout(location = 1) in vec3 color;

    layout(location = 0) out vec3 out_color;
    void main() {
        gl_Position = vec4(pos, 0.0, 1.0);
        out_color = color;
    }

``#version 450`` and ``#extension GL_ARB_separate_shader_objects : enable`` are mandatory to use vulkan.
We have to ``in`` because if we want the same triangle as this tutorial shown we need position and color on each of our vertex. Remember the ``0`` and ``1`` we will need that later.
The ``out`` declarative is too pass value to the next shader, here, it will be the fragment shader.
Call the fragment shader ``
**Fragment shader**

.. code-block:: glsl

    #version 450
    #extension GL_ARB_separate_shader_objects : enable

    layout(location = 0) out vec4 outColor;
    layout(location = 0) in vec3 color;
    void main() {
        outColor = vec4(color, 1.0);
    }

The ``in`` declaration correspond to the ``out`` declaration of our vertex shader.A side that, it's a classic fragment shader.

Ok, now we have glsl file, great...but Vulkan doesn't deal with glsl file, it deals with SPIR-V. Use ``glslangValidator``.

.. code-block:: shell

    glslangValidator -V triangle.vert -o trianglevert.spriv
    glslangValidator -V triangle.frag -o trianglefrag.spriv

After that we can create two ``mountain::shader``, one for ``vertex`` and one for ``fragment``, we store them in an arrays.

.. code-block:: cpp

    #include <array>
    ...
    // swap chain
    std::array shaders {mountain::shader{"trianglevert.spv", vk::ShaderStageFlagBits::eVertex},
                        mountain::shader{"trianglefrag.spv", vk::ShaderStageFlagBits::eFragment}};

The ``moutain::shader`` only need two parameters, the path to the spriv file (it's a ``std::fileystem::path``) and the type of shader we want to create. We use C++17 template type deduction to avoid typing the type and the size of our arrays.