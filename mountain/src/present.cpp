//
// Created by stiven_perso on 14/03/2021.
//
#include "mountain/present.h"
#include <vulkan/vulkan.h>
namespace mountain{

    Present::Present(const Context &context, const SwapChain &swapchain):
    _context(context),
    _swapchain(swapchain),
    _imageAvailableSemaphore(_context->createSemaphoreUnique({})),
    _renderFinishedSemaphore(_context->createSemaphoreUnique({})){

    }

    void Present::present(std::uint32_t const image_index, std::vector<buffer::uniform_updater> &updaters, std::vector<vk::CommandBuffer>&& command_buffers) {



        for (auto &updater : updaters) {
            updater(_context, static_cast<int>(image_index));
        }

        vk::SubmitInfo submitInfo;
        vk::Semaphore waitSemaphores[] = {*_imageAvailableSemaphore};

        vk::PipelineStageFlags waitStages[] = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = static_cast<uint32_t>(std::size(command_buffers));
        submitInfo.pCommandBuffers = command_buffers.data();

        auto const& graphics_queue = _context.get_graphics_queue();
        vk::Semaphore signalSemaphores[] = {*_renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;
        checkError(vkQueueSubmit(graphics_queue, 1, (VkSubmitInfo *) &submitInfo, VK_NULL_HANDLE),
                   "failed to submit draw command buffer!");

        vk::PresentInfoKHR presentInfo = {};

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        auto const& present_queue = _context.get_present_queue();
        vk::SwapchainKHR swapChains[] = {_swapchain.get_swap_chain()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &image_index;
        presentInfo.pResults = nullptr; // Optional
        checkError(present_queue.presentKHR(presentInfo),
                   "unable to present frame buffer"
        );
        present_queue.waitIdle();

    }



}
