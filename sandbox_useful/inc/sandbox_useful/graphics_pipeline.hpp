//width
// Created by stiven on 13/04/2020.
//

#ifndef SANDBOX_GRAPHICS_PIPELINE_H
#define SANDBOX_GRAPHICS_PIPELINE_H

#include <vulkan/vulkan.hpp>
#include <vector>
#include <array>
#include "sandbox_useful/buffer/vertex.hpp"
struct Device;
struct SwapChain;
struct RenderPass;
template<class T>
concept PushConstantType = sizeof(T) <= 256 && sizeof(T)%4 == 0;
template <PushConstantType>
struct PushConstant{
    vk::ShaderStageFlagBits shader_stage;
};
struct GraphicsPipeline{
    template <class ...Ts>
    GraphicsPipeline(Context const &device, SwapChain const &swap_chain, RenderPass const &render_pass,
                     const std::vector<buffer::vertex> &buffers, PushConstant<Ts> const& ...push_constant);
    vk::Pipeline const& get_pipeline() const {return _pipeline;}
    vk::PipelineLayout const& get_pipeline_layout() const{return *_pipeline_layout;}
    std::vector<vk::PushConstantRange> const& get_push_constant_ranges () const{return _push_constant_ranges;}
    ~GraphicsPipeline();
private:
    Context const& _device;
    vk::Pipeline _pipeline;
    vk::UniquePipelineLayout _pipeline_layout;
    std::vector<vk::PushConstantRange> _push_constant_ranges;
    vk::ShaderModule createShaderModule(std::vector<char> const & code);
    template<class ...Ts>
    void create_pipeline_layout(PushConstant<Ts> const& ...push_constant);
    void init(SwapChain const &swap_chain, RenderPass const &render_pass,
              const std::vector<buffer::vertex> &buffers);

    void create_pipeline_layout(){
        vk::PipelineLayoutCreateInfo pipelineLayoutInfo = {};
        pipelineLayoutInfo.setLayoutCount = 0; // Optional
        pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
        pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional
        _pipeline_layout = _device.get_device().createPipelineLayoutUnique(pipelineLayoutInfo);
    }
};
template<class ...Ts>
GraphicsPipeline::GraphicsPipeline(Context const &device, SwapChain const &swap_chain, RenderPass const &render_pass,
                                   const std::vector<buffer::vertex> &buffers, PushConstant<Ts> const& ...push_constant) :
        _device(device){

    create_pipeline_layout(push_constant...);
    init(swap_chain, render_pass, buffers);
}
template<class ...Ts>
void GraphicsPipeline::create_pipeline_layout(PushConstant<Ts> const& ...push_constant)
{
    int offset = 0;
    auto create_push_constant_ranges = [&offset]<class T>(PushConstant<T> const& push_constant) mutable {
        vk::PushConstantRange range(push_constant.shader_stage, offset, sizeof(T));
        offset += sizeof(T);
        return range;
    };

    std::vector push_constant_range{create_push_constant_ranges(push_constant)...};
    std::swap(_push_constant_ranges, push_constant_range);
    vk::PipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.setLayoutCount = 0; // Optional
    pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
    pipelineLayoutInfo.pushConstantRangeCount = _push_constant_ranges.size(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = _push_constant_ranges.data(); // Optional
    _pipeline_layout = _device.get_device().createPipelineLayoutUnique(pipelineLayoutInfo);

}
#endif //SANDBOX_GRAPHICS_PIPELINE_H
