//
// Created by stiven_perso on 14/03/2021.
//

#ifndef MOUNTAIN_API_PRESENT_H
#define MOUNTAIN_API_PRESENT_H
#include "mountain/uniform.h"
#include <mountain/command_buffer.h>
#include "mountain/mountainapi_export.h"
namespace mountain{
    struct Context;
    struct SwapChain;
    struct Present{

        MOUNTAINAPI_EXPORT Present(Context const& context, SwapChain const& swapchain);

        template <class ...CommandBuffers>
        void present(std::vector<buffer::uniform_updater>&& updaters, CommandBuffers const& ... command_buffers)
        requires (std::is_same_v<CommandBuffers, CommandBuffer> && ...);


    private:
        Context const& _context;
        SwapChain const& _swapchain;

        vk::UniqueSemaphore _imageAvailableSemaphore;
        vk::UniqueSemaphore _renderFinishedSemaphore;

        MOUNTAINAPI_EXPORT void present(std::uint32_t const image_index, std::vector<buffer::uniform_updater>& updaters, std::vector<vk::CommandBuffer>&& command_buffers);

    };

    template <class ...CommandBuffers>
    void Present::present(std::vector<buffer::uniform_updater>&& updaters, CommandBuffers const& ... command_buffers)
    requires (std::is_same_v<CommandBuffers, CommandBuffer> && ...){
        uint32_t image_index{};
        vkAcquireNextImageKHR(_context.get_device(), _swapchain.get_swap_chain(), std::numeric_limits<uint64_t>::max(),
                              *_imageAvailableSemaphore, VK_NULL_HANDLE, &image_index);
        present(image_index, updaters, std::vector{command_buffers.get_command_buffer(image_index)...});
    }


}
#endif //MOUNTAIN_API_PRESENT_H
