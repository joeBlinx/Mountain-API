//
// Created by stiven_perso on 2/28/21.
//

#ifndef MOUNTAIN_API_SUBPASS_H
#define MOUNTAIN_API_SUBPASS_H
#include <vulkan/vulkan.hpp>
namespace mountain{
    struct RenderPass;
    struct SubPass{
        RenderPass const* renderpass;// pointer to enable default constructor
        uint32_t index;
    };
}
#endif //MOUNTAIN_API_SUBPASS_H
