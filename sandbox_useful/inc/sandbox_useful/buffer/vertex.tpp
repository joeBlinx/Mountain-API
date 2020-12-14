
#include "vertex.hpp"

//
// Created by stiven on 12/04/2020.
//

#ifndef SANDBOX_VERTEX_H
#define SANDBOX_VERTEX_H
void vertex::create_buffer(Container auto const& container, vk::BufferUsageFlags buffer_usage, vk::UniqueBuffer& buffer, vk::UniqueDeviceMemory& buffer_memory){
    vk::DeviceSize buffer_size = sizeof(container[0]) * container.size();
    auto const& vk_device = _device.get_device();

    auto[staging_buffer, staging_memory] = _device.create_buffer_and_memory(buffer_size,
                                                                            vk::BufferUsageFlagBits::eTransferSrc,
                                                                            vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    {
        void* data{};
        utils::raii_helper::MapMemory raii_mapping(vk_device, staging_memory, 0, buffer_size, &data);
        memcpy(data, container.data(), static_cast<size_t>(buffer_size));
    }

    std::tie(buffer, buffer_memory) = _device.create_buffer_and_memory(buffer_size,
                                                                       buffer_usage | vk::BufferUsageFlagBits::eTransferDst,
                                                                       vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    _device.copy_buffer(buffer, staging_buffer, buffer_size);
}
vertex::vertex(Context const &device, vertex_description&& description, Container auto &&vertices, std::vector<uint16_t> &&indices)
        :_device(device),
        _indices_count(indices.size()),
        _description(std::move(description))
        {
    auto const& vk_device = _device.get_device();
    vk::DeviceSize buffer_size = sizeof(vertices[0]) * vertices.size();
    _indices_offset = buffer_size;
    vk::DeviceSize indices_buffer_size = indices.size() * sizeof(indices[0]);
    auto[staging_buffer, staging_memory] = _device.create_buffer_and_memory(buffer_size + indices_buffer_size,
                                                                            vk::BufferUsageFlagBits::eTransferSrc,
                                                                            vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    {
        void* data{};
        utils::raii_helper::MapMemory raii_mapping(vk_device, staging_memory, 0, buffer_size + indices_buffer_size, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(buffer_size));
        memcpy(static_cast<char*>(data) + buffer_size, indices.data(), static_cast<size_t>(indices_buffer_size));
    }

    std::tie(_buffer, _buffer_memory) = _device.create_buffer_and_memory(buffer_size + indices_buffer_size,
                                                                       vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst,
                                                                       vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    _device.copy_buffer(_buffer, staging_buffer, buffer_size + indices_buffer_size);
}

#endif //SANDBOX_VERTEX_H
