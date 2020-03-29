//
// Created by joe on 5/10/19.
//

#include "utils/log.hpp"
#include "renderPass.hpp"


RenderPass::RenderPass(vk::Device device, VkRenderPassCreateInfo RenderPass_info) :
		_device(device) {


	checkError(vkCreateRenderPass(device, &RenderPass_info, nullptr, &_renderpass),
			   "failed to create render pass!");
}

RenderPass::~RenderPass() {
	vkDestroyRenderPass(_device, _renderpass, nullptr);
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