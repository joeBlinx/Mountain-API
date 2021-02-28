//
// Created by joe on 5/10/19.
//

#include "mountain/context.h"
#include "utils/log.hpp"
#include "mountain/render_pass.h"
#include <numeric>
namespace mountain {

    constexpr auto init_subrenderpass_description(unsigned const attachment){
        vk::SubpassDescription subpass{};
        subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
        if (attachment & RenderPass::COLOR){
            subpass.colorAttachmentCount = 1;
            subpass.pColorAttachments = &RenderPass::color_reference;
        }
        if(attachment & (RenderPass::DEPTH | RenderPass::STENCIL)){
            subpass.pDepthStencilAttachment = &RenderPass::depth_reference;
        }
        return subpass;
    }

    RenderPass::~RenderPass() {
        _device.destroy(_renderpass);
    }

    vk::AttachmentDescription fill_depth_stencil(const unsigned int subpass, vk::Format const &depth) {
        vk::AttachmentDescription depth_attachment{};
        depth_attachment.format = depth;
        depth_attachment.samples = vk::SampleCountFlagBits::e1;
        depth_attachment.loadOp =
                subpass & RenderPass::DEPTH ? vk::AttachmentLoadOp::eClear
                                                 : vk::AttachmentLoadOp::eDontCare;
        depth_attachment.storeOp = vk::AttachmentStoreOp::eDontCare;
        depth_attachment.stencilLoadOp =
                subpass & RenderPass::STENCIL ? vk::AttachmentLoadOp::eClear
                                                   : vk::AttachmentLoadOp::eDontCare;
        depth_attachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
        depth_attachment.initialLayout = vk::ImageLayout::eUndefined;
        depth_attachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
        return depth_attachment;
    }

    vk::AttachmentDescription fill_color(vk::Format const &color) {
        vk::AttachmentDescription color_attachment{};

        color_attachment.format = color;
        color_attachment.samples = vk::SampleCountFlagBits::e1;
        color_attachment.loadOp = vk::AttachmentLoadOp::eClear;
        color_attachment.storeOp = vk::AttachmentStoreOp::eStore;
        color_attachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
        color_attachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
        color_attachment.initialLayout = vk::ImageLayout::eUndefined;
        color_attachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

        return color_attachment;
    }

    RenderPass::RenderPass(const Context &context, const unsigned int sub_pass) : _device(context.get_device()),
                                                                                  _color_depth_stencil(
                                                                                      sub_pass) {

        auto const &swap_chain_image_format = context.choose_swap_surface_format().format;
        auto constexpr depth_format = vk::Format::eD32SfloatS8Uint;


        vk::SubpassDescription subpass = {};
        subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;

        std::vector<vk::AttachmentDescription> attachments_desc;
        if (sub_pass & RenderPass::COLOR) {
            subpass.colorAttachmentCount = 1;
            subpass.pColorAttachments = &RenderPass::color_reference;
            attachments_desc.emplace_back(fill_color(swap_chain_image_format));
        }

        if (sub_pass & RenderPass::DEPTH
            || sub_pass & RenderPass::STENCIL) {
            subpass.pDepthStencilAttachment = &RenderPass::depth_reference;
            attachments_desc.emplace_back(fill_depth_stencil(sub_pass, depth_format));
        }

        vk::SubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        dependency.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
        dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite;


        vk::RenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments_desc.size());
        renderPassInfo.pAttachments = attachments_desc.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        _renderpass = context->createRenderPass(renderPassInfo);

    }
    std::vector<vk::SubpassDependency> create_dependencies(std::vector<vk::SubpassDependency> && dependencies){
        auto &first = dependencies.front();
        first.srcSubpass = VK_SUBPASS_EXTERNAL;
        first.dstSubpass = 0;
        if(dependencies.size() > 1){
            std::for_each(begin(dependencies) + 1, end(dependencies) - 1, [i=0](auto& depend)mutable {
                depend.srcSubpass = static_cast<uint32_t>(i);
                depend.dstSubpass = static_cast<uint32_t>(i + 1);
                i += 1;
            });
            auto& last = dependencies.back();
            last.dstSubpass = static_cast<uint32_t>(dependencies.size() - 1);
        }

        return std::move(dependencies);
    }
    RenderPass::RenderPass(const Context &context, std::vector<unsigned int> &&attachments,
                                     std::vector<vk::SubpassDependency> &&dependencies) :
                                     _device(*context),
                                     _color_depth_stencil(accumulate(begin(attachments), end(attachments), 0u, [](auto const& a, auto const& b){
                                         return a | b;
                                     })){
        assert(size(attachments) == size(dependencies) && "Attachments and dependencies must have the same size");

        auto const subpasses = [&]() {
            std::vector<vk::SubpassDescription> description;
            description.reserve(size(attachments));
            std::ranges::for_each(attachments, [&](auto const& attachment){
                description.emplace_back(init_subrenderpass_description(attachment));
            });
            return description;
        }();
        dependencies = create_dependencies(std::move(dependencies));
        auto const attachments_desc = [&]{
            auto constexpr depth_format = vk::Format::eD32SfloatS8Uint;
            auto const &swap_chain_image_format = context.choose_swap_surface_format().format;
            std::vector<vk::AttachmentDescription> temp;
            temp.reserve(2);
            if (_color_depth_stencil & RenderPass::COLOR) {
                temp.emplace_back(fill_color(swap_chain_image_format));
            }
            if (_color_depth_stencil & (RenderPass::DEPTH
                | RenderPass::STENCIL)) {
                temp.emplace_back(fill_depth_stencil(_color_depth_stencil, depth_format));
            }
            return temp;
        }();

        auto const renderPassInfo = [&] {
            vk::RenderPassCreateInfo renderPassInfo{};
            renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments_desc.size());
            renderPassInfo.pAttachments = attachments_desc.data();
            renderPassInfo.subpassCount = static_cast<uint32_t>(size(subpasses));
            renderPassInfo.pSubpasses = subpasses.data();
            renderPassInfo.dependencyCount = static_cast<uint32_t>(size(dependencies));
            renderPassInfo.pDependencies = dependencies.data();
            return renderPassInfo;
        }();

        _renderpass = context->createRenderPass(renderPassInfo);
    }

}