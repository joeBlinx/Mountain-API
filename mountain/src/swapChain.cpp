//
// Created by joe on 5/1/19.
//


#include "swapChain.h"
#include  <algorithm>
#include <renderPass.h>

namespace mountain {

    vk::PresentModeKHR chooseSwapPresentMode(std::vector<vk::PresentModeKHR> const &available_present_modes) {
        vk::PresentModeKHR bestMode = vk::PresentModeKHR::eFifo;

        for (const auto &availablePresentMode : available_present_modes) {
            if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
                return availablePresentMode;
            } else if (availablePresentMode == vk::PresentModeKHR::eImmediate) {
                bestMode = availablePresentMode;
            }
        }

        return bestMode;
    }

    vk::Extent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR const &capabilities, int width, int height) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        } else {
            vk::Extent2D actualExtent{(uint32_t) width, (uint32_t) height};

            actualExtent.width = std::max(capabilities.minImageExtent.width,
                                          std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height,
                                           std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    void SwapChain::create_swap_chain(Context const &context, int width, int height) {

        Context::SwapChainSupportDetails const &swap_chain_support = context.get_swap_chain_details();
        vk::SurfaceFormatKHR surfaceFormat = context.chooseSwapSurfaceFormat();
        vk::PresentModeKHR presentMode = chooseSwapPresentMode(swap_chain_support.presentModes);
        _swap_chain_extent = chooseSwapExtent(swap_chain_support.capabilities, width, height);


        uint32_t imageCount = swap_chain_support.capabilities.minImageCount + 1;
        if (swap_chain_support.capabilities.maxImageCount > 0 &&
            imageCount > swap_chain_support.capabilities.maxImageCount) {
            imageCount = swap_chain_support.capabilities.maxImageCount;
        }

        vk::SwapchainCreateInfoKHR createInfo = {};
        createInfo.surface = context.get_vk_surface();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = _swap_chain_extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment; // can change

        auto const &indices = context.get_queue_family_indice();
        uint32_t queueFamilyIndices[] = {static_cast<uint32_t>(indices.graphics_family),
                                         static_cast<uint32_t>(indices.present_family)};

        if (indices.graphics_family != indices.present_family) {
            createInfo.imageSharingMode = vk::SharingMode::eConcurrent; // one queue for all
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = vk::SharingMode::eExclusive; // one queue for each mode, graphics, present
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }
        createInfo.preTransform = swap_chain_support.capabilities.currentTransform; // specify transform apply to swap chain
        createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque; // alpha with other window
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE; // don't care about color pixel in other window
        //createInfo.oldSwapchain ; // no old swap chain..for now
        _swap_chain = _context->createSwapchainKHR(createInfo);

        _swap_chain_images = _context->getSwapchainImagesKHR(_swap_chain);
        _swap_chain_image_format = surfaceFormat.format;

    }

    void SwapChain::create_image_views() {

        _swap_chain_image_views.resize(_swap_chain_images.size());
        for (size_t i = 0; i < _swap_chain_image_views.size(); i++) {
            _swap_chain_image_views[i] = _context.create_2d_image_views(_swap_chain_images[i],
                                                                        _swap_chain_image_format,
                                                                        vk::ImageAspectFlagBits::eColor, 1);

        }
    }

    SwapChain::~SwapChain() {
        _context->destroy(_swap_chain);
    }

    SwapChain::SwapChain(Context const &context, RenderPass const &render_pass, int width, int height)
            : _context(context) {
        create_swap_chain(context, width, height);
        create_image_views();
        if (render_pass.has_depth()) {
            create_depth_resources();
        }
        create_frame_buffer(render_pass);
    }

    vk::SwapchainKHR SwapChain::get_swap_chain() const {
        return _swap_chain;
    }

    const std::vector<vk::UniqueImageView> &SwapChain::get_swap_chain_image_views() const {
        return _swap_chain_image_views;
    }

    vk::Format SwapChain::get_swap_chain_image_format() const {
        return _swap_chain_image_format;
    }

    const vk::Extent2D &SwapChain::get_swap_chain_extent() const {
        return _swap_chain_extent;
    }

    void SwapChain::create_depth_resources() {
        vk::Format depth_format = vk::Format::eD32SfloatS8Uint;

        std::tie(_depth_image, _depth_image_memory) = _context.create_image(
                _swap_chain_extent.width,
                _swap_chain_extent.height,
                depth_format,
                vk::ImageTiling::eOptimal,
                vk::ImageUsageFlagBits::eDepthStencilAttachment,
                vk::MemoryPropertyFlagBits::eDeviceLocal, 1);

        _depth_image_view = _context.create_2d_image_views(*_depth_image, depth_format, vk::ImageAspectFlagBits::eDepth,
                                                           1);


    }

    void SwapChain::create_frame_buffer(const RenderPass &render_pass) {
        _swapchain_frame_buffers.resize(_swap_chain_image_views.size());
        for (size_t i = 0; i < _swap_chain_image_views.size(); i++) {
            std::vector<vk::ImageView> attachments{
                    *_swap_chain_image_views[i]
            };
            if (render_pass.has_depth()) {
                attachments.emplace_back(*_depth_image_view);
            }

            vk::FramebufferCreateInfo framebufferInfo;
            framebufferInfo.renderPass = render_pass.get_renderpass();
            framebufferInfo.attachmentCount = std::size(attachments);
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = _swap_chain_extent.width;
            framebufferInfo.height = _swap_chain_extent.height;
            framebufferInfo.layers = 1;
            _swapchain_frame_buffers[i] = _context.get_device().createFramebufferUnique(framebufferInfo);

        }

    }

    std::vector<vk::Framebuffer> SwapChain::get_framebuffers() const {
        std::vector<vk::Framebuffer> framebuffers(_swapchain_frame_buffers.size());
        std::ranges::transform(_swapchain_frame_buffers, begin(framebuffers),
                               [](auto const &uniqueframebuffers) {
                                   return *uniqueframebuffers;
                               });
        return framebuffers;
    }
}