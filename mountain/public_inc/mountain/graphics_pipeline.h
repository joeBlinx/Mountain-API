//
// Created by stiven on 13/04/2020.
//

#ifndef MOUNTAIN_API_GRAPHICS_PIPELINE_H
#define MOUNTAIN_API_GRAPHICS_PIPELINE_H

#include <vulkan/vulkan.hpp>
#include <vector>
#include <array>
#include "vertex.h"
#include <filesystem>
#include "utils/utils.hpp"
namespace mountain {

    struct SwapChain;
    struct RenderPass;
    struct SubPass;
    template<class T>
    concept PushConstantType = sizeof(T) <= 256 && sizeof(T) % 4 == 0;

    /**
     * @tparam PushConstantType: type of the value we want to be a push constant
     */
    template<PushConstantType>
    struct PushConstant {
        /**
         * the stage in which the push constant will be use
         */
        vk::ShaderStageFlagBits shader_stage;
    };

    struct shader {
        /**
         * path to spir-v file
         */
        std::filesystem::path path;
        /**
         * Type of shader we pass
         */
        vk::ShaderStageFlagBits type;
    };

    struct GraphicsPipeline {
        /**
         * Create a vulkan pipeline
         * @tparam n: number of shaders
         * @tparam Ts: types of values hold by push constant
         * @param context: Vulkan context
         * @param swap_chain
         * @param render_pass
         * @param shaders: array of compiled shaders
         * @param buffers: arrays of vertex buffers
         * @param descriptor_layout: array of descriptor layout for handling uniform
         * @param push_constant: PushConstant for each shaders use
         */
        template<size_t n, class ...Ts>
        GraphicsPipeline(Context const &context, SwapChain const &swap_chain, SubPass const &render_pass,
                         std::array<shader, n> const &shaders,
                         const std::vector<buffer::vertex> &buffers,
                         std::vector<vk::DescriptorSetLayout> const &descriptor_layout = {},
                         PushConstant<Ts> const &...push_constant);
        GraphicsPipeline() = default;
        /**
         * @return: The vulkan pipeline object
         */
        vk::Pipeline const &get_pipeline() const { return *_pipeline; }

        vk::PipelineLayout const &get_pipeline_layout() const { return *_pipeline_layout; }

        std::vector<vk::PushConstantRange> const &get_push_constant_ranges() const { return _push_constant_ranges; }

    private:
        friend class PipelineBuilder;
        Context const *_device;
        vk::UniquePipeline _pipeline;
        vk::UniquePipelineLayout _pipeline_layout;
        std::vector<vk::PushConstantRange> _push_constant_ranges;

        MOUNTAINAPI_EXPORT vk::ShaderModule createShaderModule(std::vector<char> const &code);

        template<class ...Ts>
        void create_pipeline_layout(std::vector<vk::DescriptorSetLayout> const &descriptor_layout,
                                    PushConstant<Ts> const &...push_constant);

        MOUNTAINAPI_EXPORT void init(const SwapChain &swap_chain, const SubPass &sub_pass,
                                     const std::vector<buffer::vertex> &buffers,
                                     std::vector<vk::PipelineShaderStageCreateInfo> &&shaders_stages);

        template<size_t n>
        std::vector<vk::PipelineShaderStageCreateInfo> create_shader_info(std::array<shader, n> const &shaders);

        void create_pipeline_layout() {
            vk::PipelineLayoutCreateInfo pipelineLayoutInfo = {};
            pipelineLayoutInfo.setLayoutCount = 0; // Optional
            pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
            pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
            pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional
            _pipeline_layout = (*_device)->createPipelineLayoutUnique(pipelineLayoutInfo);
        }
    };

    template<size_t n, class ...Ts>
    GraphicsPipeline::GraphicsPipeline(Context const &device, SwapChain const &swap_chain,
                                       SubPass const &render_pass, std::array<shader, n> const &shaders,
                                       const std::vector<buffer::vertex> &buffers,
                                       std::vector<vk::DescriptorSetLayout> const &descriptor_layout,
                                       PushConstant<Ts> const &...push_constant) :
            _device(&device) {
        static_assert(n >= 2,
                      "shaders arrays must contains at least two entry, one vertex shader and one fragment shader");
        create_pipeline_layout(descriptor_layout, push_constant...);
        init(swap_chain, render_pass, buffers, create_shader_info(shaders));
    }

    template<class ...Ts>
    void GraphicsPipeline::create_pipeline_layout(std::vector<vk::DescriptorSetLayout> const &descriptor_layout,
                                                  PushConstant<Ts> const &...push_constant) {
        uint32_t offset = 0;
        auto create_push_constant_ranges = [&offset]<class T>(PushConstant<T> const &push_constant) mutable {
            vk::PushConstantRange range(push_constant.shader_stage, offset, static_cast<uint32_t>(sizeof(T)));
            offset += sizeof(T);
            return range;
        };
        if constexpr (sizeof...(push_constant) > 0) {
            std::vector push_constant_range{create_push_constant_ranges(push_constant)...};
            std::swap(_push_constant_ranges, push_constant_range);
        }
        vk::PipelineLayoutCreateInfo pipelineLayoutInfo = {};
        pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptor_layout.size());
        pipelineLayoutInfo.pSetLayouts = descriptor_layout.data();
        pipelineLayoutInfo.pushConstantRangeCount = static_cast<uint32_t>(_push_constant_ranges.size());
        pipelineLayoutInfo.pPushConstantRanges = _push_constant_ranges.data();
        _pipeline_layout = (*_device)->createPipelineLayoutUnique(pipelineLayoutInfo);

    }

    MOUNTAINAPI_EXPORT vk::PipelineShaderStageCreateInfo createShaderInfo(vk::ShaderModule &module, vk::ShaderStageFlagBits type);

    template<size_t n>
    std::vector<vk::PipelineShaderStageCreateInfo>
    GraphicsPipeline::create_shader_info(std::array<shader, n> const &shaders) {

        std::vector<vk::PipelineShaderStageCreateInfo> shaders_info;
        shaders_info.reserve(n);
        std::ranges::for_each(shaders, [this, &shaders_info](auto const &shader)mutable {
            std::vector<char> shader_data = utils::readFile(shader.path.string());
            auto module = createShaderModule(shader_data);
            shaders_info.emplace_back(createShaderInfo(
                    module,
                    shader.type
            ));

        });
        return shaders_info;
    }
}
#endif //SANDBOX_GRAPHICS_PIPELINE_H
