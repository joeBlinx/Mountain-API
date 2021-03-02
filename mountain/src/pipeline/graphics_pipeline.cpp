//
// Created by stiven on 13/04/2020.
//

#include "mountain/graphics_pipeline.h"
#include "utils/utils.hpp"
#include "mountain/subpass.h"
namespace mountain {

    vk::PushConstantRange const &GraphicsPipeline::get_push_constant(const vk::ShaderStageFlagBits shader_stage) const {
        auto const it = std::ranges::find_if(_push_constant_ranges, [&shader_stage](vk::PushConstantRange const& push_constant){
            return push_constant.stageFlags == shader_stage;
        });
        assert(it != end(_push_constant_ranges));
        return *it;
    }
}