#pragma once
#include "vulkan/vulkan.hpp"

template<class T, int n>
struct vertex_format;
template<class T, int n>
constexpr vk::Format vertex_format_t = vertex_format<T, n>::value;

template<class T>
struct vertex_format<T, 1>{
    static constexpr vk::Format value = vk::Format::eR32Sfloat;
};

template<class T>
struct vertex_format<T, 2>{
    static constexpr vk::Format value = vk::Format::eR32G32Sfloat;
};

template<class T>
struct vertex_format<T, 3>{
    static constexpr vk::Format value = vk::Format::eR32G32B32Sfloat;
};

template<class T>
struct vertex_format<T, 4>{
    static constexpr vk::Format value = vk::Format::eR32G32B32A32Sfloat;
};

// template<>
// struct vertex_format<int, 1>{
//     static constexpr vk::Format value = vk::Format::eR32Sint;
// };

// template<>
// struct vertex_format<int, 2>{
//     static constexpr vk::Format value = vk::Format::eR32G32Sint;
// };

// template<>
// struct vertex_format<int, 3>{
//     static constexpr vk::Format value = vk::Format::eR32G32B32Sint;
// };

// template<>
// struct vertex_format<int, 4>{
//     static constexpr vk::Format value = vk::Format::eR32G32B32A32Sint;
// };

// template<>
// struct vertex_format<unsigned int, 1>{
//     static constexpr vk::Format value = vk::Format::eR32Uint;
// };

// template<>
// struct vertex_format<unsigned int, 2>{
//     static constexpr vk::Format value = vk::Format::eR32G32Uint;
// };

// template<>
// struct vertex_format<unsigned int, 3>{
//     static constexpr vk::Format value = vk::Format::eR32G32B32Uint;
// };

// template<>
// struct vertex_format<unsigned int, 4>{
//     static constexpr vk::Format value = vk::Format::eR32G32B32A32Uint;
// };