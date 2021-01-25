#pragma once
#include <vulkan/vulkan.hpp>
#include <array>
#include <utils/type_trait.hpp>
#include <algorithm>
#include "mountain/context.hpp"
#include "utils/raii_helper.h"
namespace mountain {

    template<class T>
    constexpr vk::Format get_format() {
        return vertex_format_t<T, sizeof(T) / sizeof(uint32_t)>;
    }

    template<class T>
    struct format_offset {
        vk::Format format;
        uint32_t offset;
    };
#define NARGS(...) NARGS_(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
#define NARGS_(_6, _5, _4, _3, _2, _1, N, ...) N

#define CONC(A, B) CONC_(A, B)
#define CONC_(A, B) A##B


#define CLASS_DESCRIPTION_1(object, attrib1)  mountain::format_offset<object>{ mountain::get_format<decltype(object::attrib1)>(), offsetof(object, attrib1) }
#define CLASS_DESCRIPTION_2(object, attrib1, attrib2)  CLASS_DESCRIPTION_1(object, attrib1), mountain::format_offset<object>{ mountain::get_format<decltype(object::attrib2)>(), offsetof(object, attrib2) }
#define CLASS_DESCRIPTION_3(object, attrib1, attrib2, attrib3)   CLASS_DESCRIPTION_2(object, attrib1,  attrib2), mountain::format_offset<object>{ mountain::get_format<decltype(object::attrib3)>(), offsetof(object, attrib3) }
#define CLASS_DESCRIPTION_4(object, attrib1, attrib2, attrib3, attrib4)   CLASS_DESCRIPTION_3(object, attrib1,  attrib2, attrib3), mountain::format_offset<object>{ mountain::get_format<decltype(object::attrib4)>(), offsetof(object, attrib4) }
#define CLASS_DESCRIPTION_5(object, attrib1, attrib2, attrib3, attrib4, attrib5)  CLASS_DESCRIPTION_4(object, attrib1,  attrib2, attrib3, attrib4), mountain::format_offset<object>{ mountain::get_format<decltype(object::attrib5)>(), offsetof(object, attrib5) }
#define CLASS_DESCRIPTION_6(object, attrib1, attrib2, attrib3, attrib4, attrib5, attrib6)  CLASS_DESCRIPTION_5(object, attrib1,  attrib2, attrib3, attrib4, attrib5), mountain::format_offset<object>{ mountain::get_format<decltype(object::attrib6)>(), offsetof(object, attrib6) }

#define CLASS_DESCRIPTION(object, ...) std::array{ CONC(CLASS_DESCRIPTION_, NARGS(__VA_ARGS__)) (object, __VA_ARGS__) }
    struct Device;
    namespace buffer {
        struct vertex_description {
            size_t attributes_size;
            vk::VertexInputBindingDescription bindings;
            std::vector<vk::VertexInputAttributeDescription> attributes;

            template<class T, auto N>
            vertex_description(uint32_t binding, uint32_t location_start_from,
                               std::array<format_offset<T>, N> &&format_offsets):
                    attributes_size(format_offsets.size()),
                    bindings(binding,
                             sizeof(T),
                             vk::VertexInputRate::eVertex) {
                std::ranges::sort(format_offsets, [](auto const& format_offset_a, auto const& format_offset_b){
                    return format_offset_a.offset < format_offset_b.offset;
                });
                attributes.resize(attributes_size);
                std::generate(std::begin(attributes), std::end(attributes),
                              [form_offset = std::begin(
                                      format_offsets), location = location_start_from, binding]() mutable {
                                  vk::VertexInputAttributeDescription ret{location++, binding, form_offset->format,
                                                                          form_offset->offset};
                                  ++form_offset;
                                  return ret;
                              }
                );
            }
        };

        template<class T>
        concept Container = requires(T a){
            { a.size() };
            { a.data() };
            { a.operator[](0) };
        };

        template <class T>
        concept Container_uint32_t = requires(T){
            { std::is_same_v<typename std::remove_cvref_t<T>::value_type, uint32_t> } ;
            { Container<T> };
        };

        struct vertex {
            template<Container container, Container_uint32_t indices_container>
            vertex(Context const &device, vertex_description &&description, container &&vertices,
                   indices_container &&indices);

            vk::Buffer const &get_buffer() const { return *_buffer; }

            uint32_t get_indices_count() const { return _indices_count; }

            uint32_t get_attribute_size() const { return _description.attributes_size; }

            vk::VertexInputBindingDescription const &get_bindings() const { return _description.bindings; }

            std::vector<vk::VertexInputAttributeDescription> const &
            get_attributes() const { return _description.attributes; }

            uint32_t get_indices_offset() const { return _indices_offset; }

        private:
            template<Container container>
            void create_buffer(container const &vertices, vk::BufferUsageFlags buffer_usage, vk::UniqueBuffer &buffer,
                               vk::UniqueDeviceMemory &buffer_memory);

            Context const &_device;
            vk::UniqueDeviceMemory _buffer_memory;
            vk::UniqueBuffer _buffer;

            uint32_t _indices_count;
            vertex_description _description;
            uint32_t _indices_offset;
        };

#include "mountain/buffer/vertex.tpp"

    }
}
