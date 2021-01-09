//
// Created by joe on 5/10/19.
//

#include <context.hpp>
#include "utils/log.hpp"
#include "renderPass.hpp"


RenderPass::RenderPass(vk::Device device, VkRenderPassCreateInfo) :
		_device(device) {


//	checkError(vkCreateRenderPass(device, &RenderPass_info, nullptr, &_renderpass),
//			   "failed to create render pass!");
}

RenderPass::~RenderPass() {
	_device.destroy(_renderpass);
}

vk::AttachmentDescription fill_depth_stencil(SubPass const& subpass, vk::Format const& depth){
    vk::AttachmentDescription depth_attachment{};
    depth_attachment.format = depth;
    depth_attachment.samples = vk::SampleCountFlagBits::e1;
    depth_attachment.loadOp = subpass.attachment_depth_stencil &subpass_attachment::DEPTH? vk::AttachmentLoadOp::eClear:vk::AttachmentLoadOp::eDontCare;
    depth_attachment.storeOp = vk::AttachmentStoreOp::eDontCare;
    depth_attachment.stencilLoadOp = subpass.attachment_depth_stencil &subpass_attachment::STENCIL? vk::AttachmentLoadOp::eClear:vk::AttachmentLoadOp::eDontCare;
    depth_attachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    depth_attachment.initialLayout = vk::ImageLayout::eUndefined;
    depth_attachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
    return depth_attachment;
}
vk::AttachmentDescription fill_color(vk::Format const& color){
    vk::AttachmentDescription color_attachment{};

    color_attachment.format = color;
    color_attachment.samples = vk::SampleCountFlagBits::e1;
    color_attachment.loadOp = vk::AttachmentLoadOp::eClear;
    color_attachment.storeOp =vk::AttachmentStoreOp::eStore ;
    color_attachment.stencilLoadOp =vk::AttachmentLoadOp::eDontCare;
    color_attachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    color_attachment.initialLayout = vk::ImageLayout::eUndefined;
    color_attachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

    return color_attachment;
}

RenderPass::RenderPass(const Context &context, const SubPass &sub_pass) :_device(context.get_device()){

    auto const& swap_chain_image_format = context.chooseSwapSurfaceFormat().format;
    auto const depth_format = vk::Format::eD32SfloatS8Uint;


    vk::SubpassDescription subpass = {};
    subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;

    int index = 0;
    vk::AttachmentReference colorAttachmentRef = {};
    vk::AttachmentReference depthAttachmentRef = {};
    std::vector<vk::AttachmentDescription> attachments_desc;
    if(sub_pass.attachment_color){
        colorAttachmentRef.attachment = index++;
        colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        attachments_desc.emplace_back(fill_color(swap_chain_image_format));
    }

    if(sub_pass.attachment_depth_stencil& subpass_attachment::DEPTH
    ||  sub_pass.attachment_depth_stencil& subpass_attachment::STENCIL){

        depthAttachmentRef.attachment = index++;
        depthAttachmentRef.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;
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
    renderPassInfo.attachmentCount = attachments_desc.size();
    renderPassInfo.pAttachments = attachments_desc.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    _renderpass = context->createRenderPass(renderPassInfo);

}


template<>
vk::AttachmentDescription
fill_attachment<(unsigned)subpass_attachment::COLOR>(vk::AttachmentDescription &attachement, vk::Format const&color,
                                                     vk::Format const&)
{
    attachement.loadOp = vk::AttachmentLoadOp::eClear;
    attachement.storeOp = vk::AttachmentStoreOp::eStore;
    attachement.finalLayout = vk::ImageLayout::ePresentSrcKHR;
    attachement.format = color;
    return attachement;
}

template<>
vk::AttachmentDescription
fill_attachment<(unsigned)subpass_attachment::DEPTH>(vk::AttachmentDescription &attachement, vk::Format const&,
                                                     vk::Format const&depth)
{
    attachement.loadOp = vk::AttachmentLoadOp::eClear;
    attachement.storeOp = vk::AttachmentStoreOp::eDontCare;
    attachement.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
    attachement.format = depth;
    return attachement;
}
template<>
vk::AttachmentDescription
fill_attachment<(unsigned)subpass_attachment::STENCIL>(vk::AttachmentDescription &attachement, vk::Format const&,
                                                       vk::Format const& depth)
{
    attachement.format = depth;
    attachement.stencilLoadOp = vk::AttachmentLoadOp::eClear;
    attachement.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    attachement.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
    return attachement;
}