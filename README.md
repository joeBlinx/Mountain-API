[![Build Status](https://drone.aigle-grenier.ovh/api/badges/joeBlinx/Mountain-API/status.svg)](https://drone.aigle-grenier.ovh/joeBlinx/Mountain-API)
[![Documentation Status](https://readthedocs.org/projects/mountain-api/badge/?version=latest)](https://mountain-api.readthedocs.io/en/latest/?badge=latest)
# Mountain-API

## VERSION 0.1
Heavily based on this tutorial [https://vulkan-tutorial.com/](https://vulkan-tutorial.com/)

## Build requirements
To build the Mountain-API you'll need several things
1. Vulkan SDK https://vulkan.lunarg.com/
2. conan https://docs.conan.io/en/latest/installation.html
3. cmake (at least 3.10) https://cmake.org/download/
4. a C++20 compliant compiler (gcc-10, MSVC 19.23)

For Linux, you can use the Dockerfile provide in the docker folder.
## Build
You only have to launch cmake as you usually do with other project

To build the sample you'll need to set `BUILD_SAMPLES` to `ON`
You can build the documentation with the option `BUILD_DOCUMENTATION` to `ON`
## Documentation
https://mountain-api.readthedocs.io/en/latest/
## Next Features
- Make a loader of share library, the share library will old all of necessary command 
to draw the things i want.

- make several config possible Stencil buffer? nb of renderpass, subpasses etc...

- config file system where you put all the specific features you need 

- When we load a share lib, read a config file, destroy the previous config and load the new

