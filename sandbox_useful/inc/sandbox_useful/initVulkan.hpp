//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_INITVULKAN_HPP
#define SANDBOX_INITVULKAN_HPP

#include <vulkan/vulkan.hpp>
#include <vector>
#include "sandbox_useful/swapChain.hpp"
#include "sandbox_useful/context.hpp"
#include "sandbox_useful/renderpass/renderPass.hpp"
#include "utils/utils.hpp"
#include "sandbox_useful/buffer/vertex.hpp"
#include "sandbox_useful/buffer/vertex.hpp"
#include "sandbox_useful/graphics_pipeline.hpp"
#include <cstddef>
#include <sandbox_useful/buffer/image2d.h>
#include "sandbox_useful/buffer/uniform.h"
#include "sampler.h"

struct GraphicsPipeline;
template <class PushConstant>
struct PipelineData{
    buffer::vertex const& vertices;
    GraphicsPipeline const& graphics_pipeline;
    std::vector<PushConstant> push_constant_values;
};
struct InitVulkan {

	InitVulkan(const Context &context, const SwapChain &swap_chain, RenderPass const &renderpass, int nb_uniform = 0);
    template <class T>
    void createCommandBuffers(PipelineData<T> const& pipeline_data);

    void allocate_descriptor_set(std::vector<vk::DescriptorSetLayout> &&descriptor_set_layouts);

    template<class T>
    void update_descriptor_set(int first_descriptor_set_index, int binding,
                               const buffer::uniform<T> &uniform_buffer);

    void update_descriptor_set(int first_descriptor_set_index, int binding, buffer::image2d const& image, image::sampler const& sampler);

    void drawFrame(std::vector<buffer::uniform_updater> &&updaters);
    ~InitVulkan();

private:
#ifdef NDEBUG
	static bool constexpr _enableValidationLayer = false;
#else
	static bool constexpr _enableValidationLayer = true;
#endif
	vk::SwapchainKHR _swapchain;

	std::vector<vk::UniqueImageView> const& _swapChainImageViews;
	vk::Extent2D _swapChainExtent;
	Context const& _context;
    std::vector<vk::Framebuffer> _swapchainFrameBuffer;
	vk::CommandPool const& _commandPool;
	std::vector<vk::CommandBuffer> _commandBuffers;

    vk::UniqueDescriptorPool _descriptor_pool;
	std::vector<vk::DescriptorSet> _descriptor_sets;
	std::vector<vk::DescriptorSetLayout> _descriptor_set_layouts;
    int _nb_descriptor_set_by_image{};

	vk::Queue  _graphicsQueue;
	vk::Queue  _presentQueue;
	RenderPass const& _renderpass;

	vk::Semaphore _imageAvailableSemaphore;
	vk::Semaphore _renderFinishedSemaphore;


	void createSemaphores();

    void allocate_command_buffer();

    void create_descriptor_pool(int nb_uniform);


};


template <class T>
void InitVulkan::createCommandBuffers(PipelineData<T> const& pipeline_data)
{
    for (size_t i = 0; i < _commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        beginInfo.pInheritanceInfo = nullptr; // Optional

        checkError(vkBeginCommandBuffer(_commandBuffers[i], &beginInfo),
                   "failed to begin recording command buffer!");
        /* may be can be put into a function */
        VkRenderPassBeginInfo renderPassInfo {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = _renderpass.get_renderpass();
        renderPassInfo.framebuffer = _swapchainFrameBuffer[i];

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = _swapChainExtent;

        std::vector<VkClearValue> clear_color{
                { .color{0.5f, 0.5f, 0.5f, 1.0f} }
        };
        if(_renderpass.has_depth()){
            clear_color.emplace_back(
                    VkClearValue{.depthStencil {1.f, 0}});
        }
        renderPassInfo.clearValueCount = std::size(clear_color);
        renderPassInfo.pClearValues = clear_color.data();

        vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_data.graphics_pipeline.get_pipeline()); // bind the pipeline
        auto& vertex_buffer = pipeline_data.vertices;
//        for(auto const& vertex_buffer : buffers){
            _commandBuffers[i].bindVertexBuffers(0, 1, &vertex_buffer.get_buffer(), std::vector<vk::DeviceSize>{0}.data());
            _commandBuffers[i].bindIndexBuffer(vertex_buffer.get_buffer(), vertex_buffer.get_indices_offset(), vk::IndexType::eUint32);
            if(! _descriptor_sets.empty()) {
                _commandBuffers[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                                      pipeline_data.graphics_pipeline.get_pipeline_layout(),
                                                      0, _nb_descriptor_set_by_image, &_descriptor_sets[i*_nb_descriptor_set_by_image], 0, nullptr);
            }
            for (auto const& value: pipeline_data.push_constant_values) {
                for (auto const &push_constant_range : pipeline_data.graphics_pipeline.get_push_constant_ranges()) {
                    _commandBuffers[i].pushConstants(pipeline_data.graphics_pipeline.get_pipeline_layout(),
                                                     push_constant_range.stageFlags, push_constant_range.offset,
                                                     push_constant_range.size, (reinterpret_cast<std::byte const*>(&value)+push_constant_range.offset));
                }
            }
        vkCmdDrawIndexed(_commandBuffers[i], vertex_buffer.get_indices_count(), 1, 0, 0, 0); // draw buffer
//        }

        vkCmdEndRenderPass(_commandBuffers[i]);
        checkError(vkEndCommandBuffer(_commandBuffers[i]),
                   "failed to record command buffer!");

    }

}

template<class T>
void InitVulkan::update_descriptor_set(int first_descriptor_set_index, int binding,
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
    for(auto& uniform: uniform_buffer){
        it_buffers_infos->buffer = *uniform;
        it_buffers_infos->offset = 0;
        it_buffers_infos->range = sizeof(T);

        it_write_sets->dstSet = *it_descriptor_set;
        it_write_sets->dstBinding = binding; //this is a bug
        it_write_sets->dstArrayElement = 0 ;//that too
        it_write_sets->descriptorType= vk::DescriptorType ::eUniformBuffer;
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
    _context.get_device().updateDescriptorSets(write_sets.size(),
                                               write_sets.data(), 0, nullptr);
}

#endif //SANDBOX_INITVULKAN_HPP

