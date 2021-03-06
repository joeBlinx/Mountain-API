//
// Created by joe on 5/1/19.
//

#ifndef MOUNTAIN_API_SWAPCHAIN_H
#define MOUNTAIN_API_SWAPCHAIN_H

#include <vulkan/vulkan.hpp>
#include <vector>
#include "context.h"
#include "swapChain.h"
namespace mountain {

    struct RenderPass;
    struct Context;

    struct SwapChain {

        /**
         * Construct a Vulkan swap chain for graphics purpose
         * @param context: Vulkan context
         * @param render_pass:
         * @param width: width of the output image
         * @param height: height of the output image
         */
        MOUNTAINAPI_EXPORT SwapChain(Context const &context, RenderPass const &render_pass, int width, int height);

        SwapChain(SwapChain const &) = delete;

        SwapChain &operator=(SwapChain const &) = delete;
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        MOUNTAINAPI_EXPORT const std::vector<vk::UniqueImageView> &get_swap_chain_image_views()
        const;

        std::vector<vk::Framebuffer> get_framebuffers() const;

        vk::Format get_swap_chain_image_format() const;

        MOUNTAINAPI_EXPORT const vk::Extent2D &get_swap_chain_extent() const;

        MOUNTAINAPI_EXPORT vk::SwapchainKHR get_swap_chain() const;
#endif
        MOUNTAINAPI_EXPORT ~SwapChain();

    private:
        Context const &_context;
        vk::SwapchainKHR _swap_chain;
        vk::UniqueImageView _depth_image_view;
        vk::UniqueDeviceMemory _depth_image_memory;
        vk::UniqueImage _depth_image;
        std::vector<vk::UniqueFramebuffer> _swapchain_frame_buffers;
        std::vector<vk::UniqueImageView> _swap_chain_image_views;
        std::vector<vk::Image> _swap_chain_images;

        vk::Format _swap_chain_image_format{};
        vk::Extent2D _swap_chain_extent{};

        void create_depth_resources();

        void create_swap_chain(Context const &context, int width, int height); // there are some parameter
        void create_image_views();

        void create_frame_buffer(const RenderPass &render_pass);
    };

}
#endif //MOUNTAIN_API_SWAPCHAIN_H
