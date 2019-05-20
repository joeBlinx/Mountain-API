//
// Created by saigle on 03/05/2019.
//

#include <log.hpp>
#include "RenderPass.h"

RenderPass::RenderPass(const VkFormat &_swap_chain_image_format) {
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = _swap_chain_image_format;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT; // multi sampling -> can change
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; //-> no option because we clear and draw
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;// ->need to read info to no option
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;// -> can change
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;// -> can change
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

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
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;


    checkError(vkCreateRenderPass(_device, &renderPassInfo, nullptr, &_render_pass),
               "failed to create render pass!");
}

RenderPass::~RenderPass() {
    vkDestroyRenderPass(_device, _render_pass, nullptr);

}
