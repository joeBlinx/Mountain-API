//
// Created by joe on 5/10/19.
//

#include <log.hpp>
#include "renderPass.hpp"


RenderPass::RenderPass(vk::Device device, VkRenderPassCreateInfo renderpass_info) :
		_device(device) {


	checkError(vkCreateRenderPass(device, &renderpass_info, nullptr, &_renderpass),
			   "failed to create render pass!");
}

RenderPass::~RenderPass() {
	vkDestroyRenderPass(_device, _renderpass, nullptr);
}

