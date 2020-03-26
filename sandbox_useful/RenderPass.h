//
// Created by saigle on 03/05/2019.
//

#ifndef SANDBOX_RENDERPASS_H
#define SANDBOX_RENDERPASS_H

#include <vulkan/vulkan.hpp>
struct RenderPass {

    RenderPass(vk::Format const & swap_chain_image_format);
    ~RenderPass();
private:
    vk::RenderPass _render_pass ;
    vk::Device _device;


};


#endif //SANDBOX_RENDERPASS_H
