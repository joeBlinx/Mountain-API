#pragma once
#include <vulkan/vulkan.hpp>
#include <array>
#include <utils/type_trait.hpp>
#include <algorithm>
#include "context.h"
#include "utils/raii_helper.h"
namespace mountain {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class T>
    constexpr vk::Format get_format =
         vertex_format_t<T, sizeof(T) / sizeof(uint32_t)>;


    template<class T>
    struct format_offset {
        vk::Format format;
        uint32_t offset;
    };
#endif
/**
 *
 * @tparam T: type of the structure
 * @tparam Ts: type of the attributes
 * @param args: member pointer to attributes
 * @return an array of offset by attribute. Use to create a buffer::vertex
 */
template<class T, class ...Ts>
auto get_format_offsets(Ts T::* ... args){
    return std::array{
        format_offset<T>{
            mountain::get_format<Ts>,
           static_cast<uint32_t>(reinterpret_cast<std::uint64_t>(static_cast<void*>(&(static_cast<T*>(nullptr)->*args))))
        }...
    };
}
    namespace buffer {
        struct vertex_description {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
            uint32_t attributes_size;
            vk::VertexInputBindingDescription bindings;
            std::vector<vk::VertexInputAttributeDescription> attributes;
#endif
            /**
             *
             * @tparam T: Type of the structure use to create vertex buffer
             * @tparam N: number of attributes in the structure
             * @param binding: must be unique by pipeline
             * @param location_start_from: location refer to location in shaders. The first attribute will have
             * location=location_start_from and then we increment by 1 for every others attribute.
             * @param format_offsets: contains information about attributes, theirs offset inside the structure.
             * This is not create by hand and you should use the CLASS_DESCRIPTION macro.
             */
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
        //TODO: change Container into std::span
        struct vertex {
            /**
             * Construct a vertex bufer
             * @tparam container: a container
             * @tparam indices_container: a container of uint32_t
             * @param context: vulkan context
             * @param description: the vertex_description
             * @param vertices: the vertices to include inside the buffer
             * @param indices: the corresponding indices
             */
            template<Container container, Container_uint32_t indices_container>
            vertex(Context const &context, vertex_description &&description, container &&vertices,
                   indices_container &&indices);
#ifndef DOXYGEN_SHOULD_SKIP_THIS
            vk::Buffer const &get_buffer() const { return *_buffer; }

            uint32_t get_indices_count() const { return _indices_count; }

            uint32_t get_attribute_size() const { return _description.attributes_size; }

            vk::VertexInputBindingDescription const &get_bindings() const { return _description.bindings; }

            std::vector<vk::VertexInputAttributeDescription> const &
            get_attributes() const { return _description.attributes; }

            uint32_t get_indices_offset() const { return _indices_offset; }
#endif
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "vertex.tpp"
#endif

    }
}
