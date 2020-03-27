//
// Created by saigle on 03/05/2019.
//

#include <log.hpp>
#include "RenderPass.h"

RenderPass::RenderPass(const vk::Format &swap_chain_image_format) {
    vk::AttachmentDescription colorAttachment ;
    colorAttachment.format = swap_chain_image_format;
    colorAttachment.samples = vk::SampleCountFlagBits::e1; // multi sampling -> can change
    colorAttachment.loadOp = vk::AttachmentLoadOp::eClear; //-> no option because we clear and draw
    colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;// ->need to read info to no option
    colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;// -> can change
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;// -> can change
    colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::SubpassDescription subpass;
    subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;

    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    vk::SubpassDependency dependency;
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead; | vk::AccessFlagBits::eColorAttachmentWrite;;

    vk::RenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    _render_pass = _device.createRenderPass(renderPassInfo);
    
}

RenderPass::~RenderPass() {
    vkDestroyRenderPass(_device, _render_pass, nullptr);

}
