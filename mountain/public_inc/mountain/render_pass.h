//
// Created by joe on 5/10/19.
//

#ifndef MOUNTAIN_API_RENDERPASS_H
#define MOUNTAIN_API_RENDERPASS_H


#include <vulkan/vulkan.hpp>
#include <array>
#include "utils/log.hpp"
#include <utility>
#include "mountain/mountainapi_export.h"
namespace mountain {

    struct Context;

    /**
     * A render pass specify what will be use when we render something.
     * To be short it define, if we want to use Color, Depth, Stencil
     */
    struct RenderPass {
        static constexpr vk::AttachmentReference color_reference {0, vk::ImageLayout::eColorAttachmentOptimal};
        static constexpr vk::AttachmentReference depth_reference {1, vk::ImageLayout::eDepthStencilAttachmentOptimal};

        enum : unsigned {
            COLOR = 1u,
            DEPTH = 1u << 2u,
            STENCIL = 1u << 3u
        };

        /**
         * Create a render pass
         * @param context: Vulkan context
         * @param sub_pass: Define the subpass we will be using
         */
        MOUNTAINAPI_EXPORT RenderPass(Context const &context, const unsigned int sub_pass);

        MOUNTAINAPI_EXPORT RenderPass(Context const &context,
                                                std::vector<unsigned int> &&attachments,
                                                std::vector<vk::SubpassDependency> && dependencies);

        /**
         * @return true if renderpass will use depth
         */
        MOUNTAINAPI_EXPORT bool has_depth() const { return RenderPass::DEPTH & _color_depth_stencil; }

        /**
         * Deleted copy operation
         */
        RenderPass operator=(RenderPass const &) = delete;

        /**
         * Deleted copy constructor
         */
        RenderPass(RenderPass const &) = delete;

        /**
        * Deleted move operation
        */
        RenderPass operator=(RenderPass &&) = delete;

        /**
         * Deleted move constructor
         */
        RenderPass(RenderPass &&) = delete;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        vk::RenderPass const &get_renderpass() const { return _renderpass; }

        MOUNTAINAPI_EXPORT ~RenderPass();
#endif
    private:

        vk::Device _device = nullptr;
        vk::RenderPass _renderpass;
        unsigned _color_depth_stencil = 0;
    };

}

#endif //MOUNTAIN_API_RENDERPASS_H
