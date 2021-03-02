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

        GraphicsPipeline() = default;

        /**
         * @return: The vulkan pipeline object
         */
        vk::Pipeline const &get_pipeline() const { return *_pipeline; }

        vk::PipelineLayout const &get_pipeline_layout() const { return *_pipeline_layout; }

        std::vector<vk::PushConstantRange> const &get_push_constant_ranges() const { return _push_constant_ranges; }

        MOUNTAINAPI_EXPORT vk::PushConstantRange const &get_push_constant(const vk::ShaderStageFlagBits shader_stage) const;

    private:
        friend struct PipelineBuilder;
        vk::UniquePipeline _pipeline;
        vk::UniquePipelineLayout _pipeline_layout;
        std::vector<vk::PushConstantRange> _push_constant_ranges;

    };

}
#endif //SANDBOX_GRAPHICS_PIPELINE_H
