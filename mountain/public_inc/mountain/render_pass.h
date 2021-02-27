//
// Created by joe on 5/10/19.
//

#ifndef MOUNTAIN_API_RENDERPASS_H
#define MOUNTAIN_API_RENDERPASS_H


#include <vulkan/vulkan.hpp>
#include <array>
#include "utils/log.hpp"
#include <utility>
#include "mountain/mountainapi_export.h"
namespace mountain {

    struct Context;
    /**
     * Attachment type for RenderPass
     */
    enum subpass_attachment : unsigned {
        COLOR = 1u,
        DEPTH = 1u << 2u,
        STENCIL = 1u << 3u
    };

    /**
     * Define the subpass for RenderPass
     */
    struct SubPass {
        unsigned attachment_color{}; // must be filled with subpass_attachment
        unsigned attachment_depth_stencil = 0; // must be filled with subpass_attachment
    };
    /**
     * A render pass specify what will be use when we render something.
     * To be short it define, if we want to use Color, Depth, Stencil
     */
    struct RenderPass {
        /**
         * Create a render pass
         * @param context: Vulkan context
         * @param sub_pass: Define the subpass we will be using
         */
        MOUNTAINAPI_EXPORT RenderPass(Context const &context, const SubPass &sub_pass);

        /**
         * @return true if renderpass will use depth
         */
        MOUNTAINAPI_EXPORT bool has_depth() const { return subpass_attachment::DEPTH & _color_depth_stencil; }

        /**
         * Deleted copy operation
         */
        RenderPass operator=(RenderPass const &) = delete;

        /**
         * Deleted copy constructor
         */
        RenderPass(RenderPass const &) = delete;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        vk::RenderPass const &get_renderpass() const { return _renderpass; }

        template<SubPass ...attachment>
        static RenderPass create(vk::Device device, vk::Format const &swap_chain_image_format);

        MOUNTAINAPI_EXPORT ~RenderPass();
#endif
    private:

        vk::Device _device = nullptr;

        RenderPass(vk::Device device, VkRenderPassCreateInfo renderpass_info);

        vk::RenderPass _renderpass;
        unsigned _color_depth_stencil = 0;
    };


    template<unsigned attach>
    constexpr VkImageLayout get_corresponding_attachment();

    template<>
    constexpr VkImageLayout get_corresponding_attachment<(unsigned) subpass_attachment::COLOR>() {
        return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }

    template<>
    constexpr VkImageLayout get_corresponding_attachment<(unsigned) subpass_attachment::DEPTH>() {
        return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    template<>
    constexpr VkImageLayout get_corresponding_attachment<(unsigned) subpass_attachment::STENCIL>() {
        return get_corresponding_attachment<(unsigned) subpass_attachment::DEPTH>();
    }

    template<unsigned attach>
    vk::AttachmentDescription
    fill_attachment(vk::AttachmentDescription &attachement, vk::Format const &, vk::Format const &) {
        return attachement;
    }

    template<>
    vk::AttachmentDescription
    fill_attachment<(unsigned) subpass_attachment::COLOR>(vk::AttachmentDescription &attachement,
                                                          vk::Format const &color,
                                                          vk::Format const &);

    template<>
    vk::AttachmentDescription
    fill_attachment<(unsigned) subpass_attachment::DEPTH>(vk::AttachmentDescription &attachement, vk::Format const &,
                                                          vk::Format const &depth);

    template<>
    vk::AttachmentDescription
    fill_attachment<(unsigned) subpass_attachment::STENCIL>(vk::AttachmentDescription &attachement, vk::Format const &,
                                                            vk::Format const &depth);

    template<int n, unsigned reference>
    constexpr VkAttachmentReference get_attachement() {
        return VkAttachmentReference
                {
                        .attachment = n,
                        .layout = get_corresponding_attachment<reference>()
                };
    }

    template<unsigned ...reference, std::size_t... I>
    constexpr std::array<VkAttachmentReference, sizeof...(I)> a2t_impl(std::index_sequence<I...>) {
        return {get_attachement<I, reference>()...};
    }

    template<unsigned ...references, typename Indices = std::make_index_sequence<sizeof...(references)>>
    constexpr std::array<VkAttachmentReference, sizeof...(references)> a2t() {
        return a2t_impl<references...>(Indices{});
    }

    template<unsigned ... references>
    constexpr std::array<VkAttachmentReference, sizeof...(references)> pack() {
        return a2t<references...>();

    }

    template<SubPass subpass, template<unsigned> class Function, class ... Args>
    constexpr decltype(auto) apply_for_all_case(Args &...args) {
        auto color = Function<subpass.attachment_color & subpass_attachment::COLOR>()(args...);
        Function<subpass.attachment_depth_stencil & subpass_attachment::DEPTH>()(args...);
        return std::pair{color, Function<subpass.attachment_depth_stencil & subpass_attachment::STENCIL>()(args...)};

    }

    template<unsigned N>
    struct wrapper {
        constexpr vk::AttachmentDescription
        operator()(vk::AttachmentDescription &attachmentDescription, vk::Format const &color, vk::Format const &depth) {
            return fill_attachment<N>(attachmentDescription, color, depth);
        }
    };

    template<SubPass... attachment>
    constexpr
    std::array<std::pair<vk::AttachmentDescription, vk::AttachmentDescription>, sizeof...(attachment)>
    fill_attachments(vk::Format const &color, vk::Format const &depth) {
        vk::AttachmentDescription attachment_desc{
                vk::AttachmentDescriptionFlags(),
                vk::Format{},
                vk::SampleCountFlagBits::e1,
                vk::AttachmentLoadOp::eDontCare,
                vk::AttachmentStoreOp::eDontCare,
                vk::AttachmentLoadOp::eDontCare,
                vk::AttachmentStoreOp::eDontCare,
                vk::ImageLayout::eUndefined,
                vk::ImageLayout::eUndefined
        };

        return {apply_for_all_case<attachment, wrapper>(attachment_desc, color, depth)...};
    }

    template<SubPass... attachment>
    RenderPass RenderPass::create(vk::Device device, vk::Format const &swap_chain_image_format) {


        auto attachments_desc = fill_attachments<attachment...>(swap_chain_image_format, swap_chain_image_format);

        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = attachments_desc.size();
        renderPassInfo.pAttachments = reinterpret_cast<VkAttachmentDescription *>(attachments_desc.data());
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        return RenderPass(device, renderPassInfo);
    }

}

#endif //MOUNTAIN_API_RENDERPASS_H
