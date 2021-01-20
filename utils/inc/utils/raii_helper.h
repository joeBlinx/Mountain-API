#pragma once
#include <vulkan/vulkan.hpp>
#include "utils/log.hpp"
namespace utils::raii_helper{
    struct MapMemory{

        MapMemory(vk::Device const& device, vk::UniqueDeviceMemory& device_memory, uint32_t offset, uint32_t size, void**data):_device(device),
        _device_memory(device_memory){
            checkError(_device.mapMemory(*_device_memory, offset, size, vk::MemoryMapFlags(), data),
                       "unable to map memory");
        }
        
        ~MapMemory(){
            _device.unmapMemory(*_device_memory);
        }
    private:
        vk::Device const& _device;
        vk::UniqueDeviceMemory& _device_memory;
    };

    struct OneTimeCommands{
        OneTimeCommands(mountain::Context const& context):_context(context){
            vk::CommandBufferAllocateInfo allocInfo{};
            allocInfo.level = vk::CommandBufferLevel::ePrimary;
            allocInfo.commandPool = _context.get_command_pool();
            allocInfo.commandBufferCount = 1;

            //allocateCommandBuffersUnique return a vector, so we take the first "front" and std::move because it is unique
            _command_buffer = std::move(_context->allocateCommandBuffersUnique(allocInfo).front());

            vk::CommandBufferBeginInfo beginInfo{};
            beginInfo.flags =
                    vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
            _command_buffer->begin(beginInfo);
        }
        vk::CommandBuffer const* operator->()const{
            return & *_command_buffer;
        }
        ~OneTimeCommands(){
            _command_buffer->end();
            vk::SubmitInfo submit_info{};
            submit_info.commandBufferCount = 1;
            submit_info.pCommandBuffers = &*_command_buffer;
            checkError(_context.get_graphics_queue().submit(1, &submit_info, nullptr),
                       "unable to submit commands");
            _context.get_graphics_queue().waitIdle();

        }
    private:
        vk::UniqueCommandBuffer _command_buffer;
        mountain::Context const& _context;


    };
}