//
// Created by saigle on 03/05/2019.
//

#ifndef SANDBOX_RENDERPASS_H
#define SANDBOX_RENDERPASS_H

#include <vulkan/vulkan.h>
struct RenderPass {

    RenderPass(VkFormat const &_swap_chain_image_format);
    ~RenderPass();
private:
    VkRenderPass _render_pass = nullptr;
    VkDevice _device = nullptr;


};


#endif //SANDBOX_RENDERPASS_H
