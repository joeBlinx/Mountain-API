//
// Created by joe on 05/08/18.
//

#ifndef MOUNTAIN_API_INITVULKAN_H
#define MOUNTAIN_API_INITVULKAN_H

#include <vulkan/vulkan.hpp>
#include <vector>
#include "swapChain.h"
#include "context.h"
#include "render_pass.h"
#include "utils/utils.hpp"
#include "vertex.h"
#include "vertex.h"
#include "graphics_pipeline.h"
#include <cstddef>
#include "image2d.h"
#include "uniform.h"
#include "sampler.h"

namespace mountain {

    struct GraphicsPipeline;
    /**
     * Pipeline Data will define how many entities of the same vertex buffer
     * will be render. This number is the size of the push_constant_values
     * @tparam PushConstantType: type of push constant to use in shaders
     */
    template<class PushConstantType>
    struct PipelineData{
        buffer::vertex const &vertices;
        GraphicsPipeline const &graphics_pipeline;
        /**
         * an array of push_constant value per object.
         * The size of this container will determine the number of object rendered
         */
        std::vector<PushConstantType> push_constant_values;
    };

    struct CommandBuffer {
        /**
         * Create CommandBuffer object
         * @param context: Vulkan context
         * @param swap_chain
         * @param renderpass
         * @param nb_uniform: number of uniform we want to use (image sample count as uniform)
         */
        MOUNTAINAPI_EXPORT CommandBuffer(const Context &context, const SwapChain &swap_chain, RenderPass const &renderpass,
                      int nb_uniform = 0);

        /**
         *
         * @tparam Function: type of the function
         * @param record_function: function that take two parameters a CommandBuffer const& and std::size_t const
         *
         * This parameter will contain a function that implement the drawing logic like bind Vertex buffer, bind Index buffer,
         * drawing command etc..
         *
         * the std::size_t const parameter of the passed function is use to retrieve a vuilkan command buffer. It's an index
         * of the command buffer currently used
         */
        template <class Function>
        void record(Function&& record_function)
        requires std::is_invocable_v<Function, CommandBuffer const&, std::size_t const>;

        /**
         *
         * @param i: the index we want
         * @return The ith vulkan command buffer
         */
        MOUNTAINAPI_EXPORT vk::CommandBuffer const& get_command_buffer(std::size_t const i)const{return _commandBuffers[i];}

        /**
         * @deprecated this method will surely be removed at one point
         * To bind a descriptor set we need several things like the a pointer to descriptor and a size to determine how many
         * descriptor we will bind. This function provide this two things for the ith image of swapchain
         * @param i: the index we want
         * @return a pair that contain a pointer to descriptor set and the number of descriptor set to bind
         */
        MOUNTAINAPI_EXPORT std::pair<vk::DescriptorSet const*, std::uint32_t>
        get_descriptor_set_size(std::size_t const i) const{
            return {&_descriptor_sets[i * _nb_descriptor_set_by_image], _nb_descriptor_set_by_image};}

        /**
         *  Allocate the number of descriptor set layout we need, the size of vector parameter X the number of image in swap chain
         * @param descriptor_set_layouts
         */
        MOUNTAINAPI_EXPORT void allocate_descriptor_set(std::vector<vk::DescriptorSetLayout> &&descriptor_set_layouts);

        /**
         * Update uniform descriptor set
         * @tparam T: type of value for the uniform
         * @param first_descriptor_set_index: set value for this descriptor
         * @param binding: binding value
         * @param uniform_buffer: uniform buffer to associate with this descriptor
         */
        template<class T>
        void update_descriptor_set(int first_descriptor_set_index, int binding,
                                   const buffer::uniform<T> &uniform_buffer);

        /**
         * Update image descriptor set

         * @param first_descriptor_set_index: set value for this descriptor
         * @param binding: binding value
         * @param image: image to associate with this descriptor
         * @param sampler: sample to associate with this image
         */
        MOUNTAINAPI_EXPORT void update_descriptor_set(int first_descriptor_set_index, int binding, buffer::image2d const &image,
                                   image::sampler const &sampler);
        /**
         * Draw frame with the record command buffers and update uniform values
         * @param updaters: vector of uniform_updater. uniform_updater are created by calling
         * ``get_uniform_updater`` on a mountain::buffer::uniform object
         */
        MOUNTAINAPI_EXPORT void drawFrame(std::vector<buffer::uniform_updater> &&updaters);

        MOUNTAINAPI_EXPORT vk::UniqueDescriptorPool const& get_descriptor_pool() const{return _descriptor_pool;}

        MOUNTAINAPI_EXPORT ~CommandBuffer();

    private:
#ifdef NDEBUG
        static bool constexpr _enableValidationLayer = false;
#else
        static bool constexpr _enableValidationLayer = true;
#endif
        vk::SwapchainKHR _swapchain;

        std::vector<vk::UniqueImageView> const &_swapChainImageViews;
        vk::Extent2D _swapChainExtent;
        Context const &_context;
        std::vector<vk::Framebuffer> _swapchainFrameBuffer;
        vk::CommandPool const &_commandPool;
        std::vector<vk::CommandBuffer> _commandBuffers;

        vk::UniqueDescriptorPool _descriptor_pool;
        std::vector<vk::DescriptorSet> _descriptor_sets;
        std::vector<vk::DescriptorSetLayout> _descriptor_set_layouts;
        uint32_t _nb_descriptor_set_by_image{};

        vk::Queue _graphicsQueue;
        vk::Queue _presentQueue;
        RenderPass const &_renderpass;

        vk::Semaphore _imageAvailableSemaphore;
        vk::Semaphore _renderFinishedSemaphore;


        void createSemaphores();

        void allocate_command_buffer();

        void create_descriptor_pool(int nb_uniform);


    };

    template<class T>
    void CommandBuffer::update_descriptor_set(int first_descriptor_set_index, int binding,
                                              const buffer::uniform<T> &uniform_buffer) {
        /*
        * We use one descriptor set layout by image of the swap chain,
        * but for using multiple set layout, we store them as follow:
        * |A|B|A|B|A|B|
        * where A and B are different descriptor set layout
        *
        */
        std::vector<vk::WriteDescriptorSet> write_sets(uniform_buffer.size());
        std::vector<vk::DescriptorBufferInfo> buffer_infos(uniform_buffer.size());
        auto it_descriptor_set = begin(_descriptor_sets) + first_descriptor_set_index;
        auto it_write_sets = begin(write_sets);
        auto it_buffers_infos = begin(buffer_infos);
        for (auto &uniform: uniform_buffer) {
            it_buffers_infos->buffer = *uniform;
            it_buffers_infos->offset = 0;
            it_buffers_infos->range = sizeof(T);

            it_write_sets->dstSet = *it_descriptor_set;
            it_write_sets->dstBinding = binding; //this is a bug
            it_write_sets->dstArrayElement = 0;//that too
            it_write_sets->descriptorType = vk::DescriptorType::eUniformBuffer;
            it_write_sets->descriptorCount = 1;
            it_write_sets->pBufferInfo = &*it_buffers_infos;
            it_write_sets->pImageInfo = nullptr;
            it_write_sets->pTexelBufferView = nullptr;

            it_write_sets++;
            it_buffers_infos++;
            it_descriptor_set += _nb_descriptor_set_by_image;
            /*
             *  |A|B|A|B|A|B| we pass from A to the other A
             * */
        }
        _context.get_device().updateDescriptorSets(static_cast<uint32_t>(write_sets.size()),
                                                   write_sets.data(), 0, nullptr);
    }

    template<class T>
    void CommandBuffer::record(T&& record_function)
    requires std::is_invocable_v<T, CommandBuffer const&, std::size_t const>{
        for (size_t i = 0; i < _commandBuffers.size(); i++) {
            auto const& command_buffer = _commandBuffers[i];
            vk::CommandBufferBeginInfo beginInfo = {};
            beginInfo.flags = vk::CommandBufferUsageFlagBits::eSimultaneousUse;
            command_buffer.begin(beginInfo);

            vk::RenderPassBeginInfo render_pass_info{};
            render_pass_info.renderPass = _renderpass.get_renderpass();
            render_pass_info.framebuffer = _swapchainFrameBuffer[i];

            render_pass_info.renderArea.offset = vk::Offset2D{0, 0};
            render_pass_info.renderArea.extent = _swapChainExtent;

            std::vector<vk::ClearValue> clear_color{
                    vk::ClearValue(
                            vk::ClearColorValue{
                                std::array{0.5f, 0.5f, 0.5f, 1.0f}})
            };
            if (_renderpass.has_depth_or_stencil()) {
                clear_color.emplace_back(
                        vk::ClearValue{{1.f, 0}});
            }
            render_pass_info.clearValueCount = static_cast<uint32_t>(std::size(clear_color));
            render_pass_info.pClearValues = clear_color.data();

            command_buffer.beginRenderPass(render_pass_info, vk::SubpassContents::eInline);
            record_function(*this, i);

            vkCmdEndRenderPass(_commandBuffers[i]);
            checkError(vkEndCommandBuffer(_commandBuffers[i]),
                       "failed to record command buffer!");

        }
    }
}
#endif //MOUNTAIN_API_INITVULKAN_H

