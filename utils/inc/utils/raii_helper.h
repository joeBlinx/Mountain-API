#pragma once
#include <vulkan/vulkan.hpp>
namespace utils::raii_helper{
    struct MapMemory{

        MapMemory(vk::Device const& device, vk::UniqueDeviceMemory& device_memory, uint32_t offset, uint32_t size, void**data):_device(device),
        _device_memory(device_memory){
            _device.mapMemory(*_device_memory, offset, size, vk::MemoryMapFlags::, data);
        }
        
        ~MapMemory(){
            _device.unmapMemory(*_device_memory);
        }
    private:
        vk::Device const& _device;
        vk::UniqueDeviceMemory& _device_memory;
    };
}