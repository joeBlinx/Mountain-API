//
// Created by stiven on 13/04/2020.
//

#ifndef SANDBOX_GRAPHICS_PIPELINE_H
#define SANDBOX_GRAPHICS_PIPELINE_H

#include <vulkan/vulkan.hpp>
#include <vector>
#include "sandbox_useful/buffer/vertex.hpp"
struct Device;
struct SwapChain;
struct RenderPass;
struct GraphicsPipeline{
    GraphicsPipeline(Device const &device, SwapChain const &swap_chain, RenderPass const &render_pass,
                     const std::vector<buffer::vertex> &buffers);
    vk::Pipeline const& get_pipeline() const {return _pipeline;}
    ~GraphicsPipeline();
private:
    Device const& _device;
    vk::Pipeline _pipeline;
    vk::UniquePipelineLayout _pipeline_layout;

    vk::ShaderModule createShaderModule(std::vector<char> const & code);

    void create_pipeline_layout();
};
#endif //SANDBOX_GRAPHICS_PIPELINE_H
