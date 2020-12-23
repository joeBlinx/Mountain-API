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
#include "sandbox_useful/buffer/uniform.h"

struct GraphicsPipeline;
template <class PushConstant>
struct PipelineData{
    buffer::vertex const& vertices;
    GraphicsPipeline const& graphics_pipeline;
    std::vector<PushConstant> push_constant_values;
};
struct InitVulkan {

	InitVulkan(const Context &context, const SwapChain &swap_chain, RenderPass const &renderpass, int nb_uniform);
    template <class T>
    void createCommandBuffers(PipelineData<T> const& pipeline_data);
    template<class ...Ts>
    void create_descriptor_sets_uniforms(
            std::vector<vk::DescriptorSetLayout> const& descriptor_set_layouts,
            buffer::uniform<Ts> const& ... uniform_buffers);
    void drawFrame(std::vector<buffer::uniform_updater> &&updaters);
    ~InitVulkan();

private:
#ifdef NDEBUG
	static bool constexpr _enableValidationLayer = false;
#else
	static bool constexpr _enableValidationLayer = true;
#endif
	vk::SwapchainKHR _swapchain;

	std::vector<vk::ImageView> const& _swapChainImageViews;
	vk::Extent2D _swapChainExtent;
	Context const& _context;
    std::vector<vk::Framebuffer> _swapchainFrameBuffer;
	vk::CommandPool const& _commandPool;
	std::vector<vk::CommandBuffer> _commandBuffers;

	vk::DescriptorPool _descriptor_pool;
	std::vector<vk::DescriptorSet> _descriptor_sets;


	vk::Queue  _graphicsQueue;
	vk::Queue  _presentQueue;
	vk::RenderPass _renderpass;

	vk::Semaphore _imageAvailableSemaphore;
	vk::Semaphore _renderFinishedSemaphore;


	void createSemaphores();

	void createFrameBuffers();

    void allocate_command_buffer();

    void create_descriptor_pool(int nb_uniform);


};


template<class ...Ts>
void InitVulkan::create_descriptor_sets_uniforms(
        std::vector<vk::DescriptorSetLayout> const& descriptor_set_layouts,
        buffer::uniform<Ts> const& ... uniform_buffers) {
    /*
     * We use one descriptor set layout by image of the swap chain,
     * but for using multiple set layout, we store them as follow:
     * |A|A|A|B|B|B|
     * where A and B are different descriptor set layout
     */
    std::vector<vk::DescriptorSetLayout> layouts;
    layouts.reserve(_swapChainImageViews.size() * descriptor_set_layouts.size());
    std::for_each(begin(descriptor_set_layouts), end(descriptor_set_layouts),
                  [&layouts, image_nb = _swapChainImageViews.size()](auto set_layout)mutable{
                      for(size_t i = 0; i < image_nb; i++){
                          layouts.emplace_back(set_layout);
                      }
                  });
    vk::DescriptorSetAllocateInfo allo_info{};
    allo_info.descriptorPool = _descriptor_pool;
    allo_info.descriptorSetCount = layouts.size();
    allo_info.pSetLayouts = layouts.data();

    _descriptor_sets.resize(layouts.size());
    checkError(
            _context.get_device().allocateDescriptorSets(&allo_info, _descriptor_sets.data()),
            "Failed to allocate descriptor set"
    );
    /*
     * the following function can be enhance
     */
    for (auto it = begin(_descriptor_sets); it != end(_descriptor_sets);){
        auto configure_descriptor_set = [this, &it]<class T>(buffer::uniform<T>const & uniform_buffer)mutable{
            std::vector<vk::WriteDescriptorSet> write_sets(uniform_buffer.size());
            std::vector<vk::DescriptorBufferInfo> buffer_infos(uniform_buffer.size());

            auto it_write_sets = begin(write_sets);
            auto it_buffers_infos = begin(buffer_infos);
            for(auto& uniform: uniform_buffer){
                it_buffers_infos->buffer = *uniform;
                it_buffers_infos->offset = 0;
                it_buffers_infos->range = sizeof(T);

                it_write_sets->dstSet = *it;
                it_write_sets->dstBinding = 0; //this is a bug
                it_write_sets->dstArrayElement = 0 ;//that too
                it_write_sets->descriptorType= vk::DescriptorType ::eUniformBuffer;
                it_write_sets->descriptorCount = 1;
                it_write_sets->pBufferInfo = &*it_buffers_infos;
                it_write_sets->pImageInfo = nullptr;
                it_write_sets->pTexelBufferView = nullptr;

                it++;
                it_write_sets++;
                it_buffers_infos++;
            }
            _context.get_device().updateDescriptorSets(write_sets.size(),
                                                       write_sets.data(), 0, nullptr);
        };
        (configure_descriptor_set(uniform_buffers), ...);
    }

}

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
        renderPassInfo.renderPass = _renderpass;
        renderPassInfo.framebuffer = _swapchainFrameBuffer[i];

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = _swapChainExtent;

        VkClearValue clearColor = { 0.5f, 0.5f, 0.5f, 1.0f };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_data.graphics_pipeline.get_pipeline()); // bind the pipeline
        auto& vertex_buffer = pipeline_data.vertices;
//        for(auto const& vertex_buffer : buffers){
            _commandBuffers[i].bindVertexBuffers(0, 1, &vertex_buffer.get_buffer(), std::vector<vk::DeviceSize>{0}.data());
            _commandBuffers[i].bindIndexBuffer(vertex_buffer.get_buffer(), vertex_buffer.get_indices_offset(), vk::IndexType::eUint16);
            if(! _descriptor_sets.empty()) {
                _commandBuffers[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                                      pipeline_data.graphics_pipeline.get_pipeline_layout(),
                                                      0, 1, &_descriptor_sets[i], 0, nullptr);
            }
            for (auto const& value: pipeline_data.push_constant_values) {
                for (auto const &push_constant_range : pipeline_data.graphics_pipeline.get_push_constant_ranges()) {
                    _commandBuffers[i].pushConstants(pipeline_data.graphics_pipeline.get_pipeline_layout(),
                                                     push_constant_range.stageFlags, push_constant_range.offset,
                                                     push_constant_range.size, (reinterpret_cast<std::byte const*>(&value)+push_constant_range.offset));
                }
                vkCmdDrawIndexed(_commandBuffers[i], vertex_buffer.get_indices_count(), 1, 0, 0, 0); // draw buffer
            }
//        }

        vkCmdEndRenderPass(_commandBuffers[i]);
        checkError(vkEndCommandBuffer(_commandBuffers[i]),
                   "failed to record command buffer!");

    }

}
#endif //SANDBOX_INITVULKAN_HPP

