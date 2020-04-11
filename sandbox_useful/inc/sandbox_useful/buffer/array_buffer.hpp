#pragma once
#include <vulkan/vulkan.hpp>
#include <array>
#include <utils/type_trait.hpp>
#include <algorithm>
#include "sandbox_useful/device.hpp"
#include "utils/raii_helper.h"
template<class T>
constexpr vk::Format get_format(){
    return vertex_format_t<T, sizeof(T)/sizeof(uint32_t)> ;
}
template<class T>
struct format_offset{
    vk::Format format;
    uint32_t offset;
};
#define NARGS(...) NARGS_(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
#define NARGS_(_6, _5, _4, _3, _2, _1, N, ...) N

#define CONC(A, B) CONC_(A, B)
#define CONC_(A, B) A##B


#define CLASS_DESCRIPTION_1(object, attrib1)  format_offset<object>{ get_format<decltype(object::attrib1)>(), offsetof(object, attrib1) }
#define CLASS_DESCRIPTION_2(object, attrib1, attrib2)  CLASS_DESCRIPTION_1(object, attrib1), format_offset<object>{ get_format<decltype(object::attrib2)>(), offsetof(object, attrib2) }
#define CLASS_DESCRIPTION_3(object, attrib1, attrib2, attrib3)   CLASS_DESCRIPTION_2(object, attrib1,  attrib2), format_offset<object>{ get_format<decltype(object::attrib3)>(), offsetof(object, attrib3) }
#define CLASS_DESCRIPTION_4(object, attrib1, attrib2, attrib3, attrib4)   CLASS_DESCRIPTION_3(object, attrib1,  attrib2, attrib3), format_offset<object>{ get_format<decltype(object::attrib4)>(), offsetof(object, attrib4) }
#define CLASS_DESCRIPTION_5(object, attrib1, attrib2, attrib3, attrib4, attrib5)  CLASS_DESCRIPTION_4(object, attrib1,  attrib2, attrib3, attrib4), format_offset<object>{ get_format<decltype(object::attrib5)>(), offsetof(object, attrib5) }
#define CLASS_DESCRIPTION_6(object, attrib1,  attrib2, attrib3, attrib4, attrib5 ,attrib6)  CLASS_DESCRIPTION_5(object, attrib1,  attrib2, attrib3, attrib4, attrib5), format_offset<object>{ get_format<decltype(object::attrib6)>(), offsetof(object, attrib6) }

#define CLASS_DESCRIPTION(object, ...) std::array{ CONC(CLASS_DESCRIPTION_, NARGS(__VA_ARGS__)) (object, __VA_ARGS__) }
class Device;
namespace buffer{
    namespace array{
        template<class T, size_t n>
        struct vertex_description{
            static constexpr size_t attributes_size = n;
            vk::VertexInputBindingDescription bindings;
            std::array<vk::VertexInputAttributeDescription, n> attributes;
            
            vertex_description(uint32_t binding, uint32_t location_start_from, std::array<format_offset<T>, n> const& format_offsets):
            bindings(binding,
                    sizeof(T),
                    vk::VertexInputRate::eVertex)
            { 
                std::generate(std::begin(attributes), std::end(attributes),
                            [form_offset = std::begin(format_offsets), location = location_start_from, binding] () mutable {
                            vk::VertexInputAttributeDescription ret{location++, binding,form_offset->format, form_offset->offset};
                            ++form_offset;
                            return ret;
                        }
        );
                    
            }
            
        };
    }
    template<class T>
    concept bool Container = requires(T a){
        {a.size()} -> size_t;
        {a.data()};
    };
    struct vertex{
        template<Container container>
        vertex(Device const& device, container && vertices):_vk_device(device.get_device())
    	{	
           
            vk::DeviceSize buffer_size = sizeof(vertices[0]) * vertices.size();
            std::tie(_buffer, _buffer_memory) = device.create_buffer_and_memory(buffer_size, vk::BufferUsageFlagBits::eVertexBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
           
            _vk_device.bindBufferMemory(*_buffer, *_buffer_memory, 0);
            {
                void* data{};
                utils::raii_helper::MapMemory raii_mapping(_vk_device, _buffer_memory, 0, buffer_size, &data);
                memcpy(data, vertices.data(), static_cast<size_t>(buffer_size));
            }

	    }
        operator vk::Buffer const&() const{
            return *_buffer;
        }
    private:
        vk::Device _vk_device;
        vk::UniqueBuffer _buffer;
        vk::UniqueDeviceMemory _buffer_memory;
    };
}
