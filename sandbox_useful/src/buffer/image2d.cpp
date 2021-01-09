//
// Created by stiven_perso on 1/5/21.
//

#include "buffer/image2d.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <context.hpp>
#include <uniform.h>
#include "utils/log.hpp"
buffer::image2d::image2d(Context const &context, fs::path const &image_path) {

    int tex_width, tex_height, texChannels;
    std::unique_ptr<stbi_uc, decltype(
            [](auto pixels){
                stbi_image_free(pixels);
            }
            )> pixels(stbi_load(image_path.c_str(), &tex_width, &tex_height, &texChannels, STBI_rgb_alpha));
    vk::DeviceSize image_size = tex_width * tex_height * 4;
    if (!pixels) {
        throw std::runtime_error("failed to load texture image!");
    }

    auto[staging_buffer_memory, staging_buffer]
    = context.create_buffer_and_memory(
            image_size,
            vk::BufferUsageFlagBits::eTransferSrc,
            vk::MemoryPropertyFlagBits::eHostVisible |
            vk::MemoryPropertyFlagBits::eHostCoherent
            );

    {
        void* data;
        utils::raii_helper::MapMemory map(context.get_device(), staging_buffer_memory,
                                      0, image_size, &data);
        std::memcpy(data, pixels.get(), image_size);
    }

   std::tie(_image, _image_memory) = context.create_image(tex_width, tex_height,
                                                       vk::Format::eR8G8B8A8Srgb,
                                                       vk::ImageTiling::eOptimal,
                                                       vk::ImageUsageFlagBits::eTransferDst
                                                       | vk::ImageUsageFlagBits::eSampled,
                                                       vk::MemoryPropertyFlagBits::eDeviceLocal);
   transition_image_layout(
            context,
            vk::Format::eR8G8B8A8Srgb,
            vk::ImageLayout::eUndefined,
            vk::ImageLayout::eTransferDstOptimal
    );
    context.copy_buffer_to_image(*staging_buffer,
                                 *_image,
                                 tex_width,
                                 tex_height);
    transition_image_layout(
            context,
            vk::Format::eR8G8B8A8Srgb,
            vk::ImageLayout::eTransferDstOptimal,
            vk::ImageLayout::eShaderReadOnlyOptimal
            );
}

void
buffer::image2d::transition_image_layout(Context const &context, [[maybe_unused]] vk::Format format, vk::ImageLayout old_layout,
                                         vk::ImageLayout new_layout) {
    utils::raii_helper::OneTimeCommands command(context);

    vk::ImageMemoryBarrier barrier{};
    barrier.oldLayout = old_layout;
    barrier.newLayout = new_layout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = *_image;
    barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    vk::PipelineStageFlags source_stage;
    vk::PipelineStageFlags destination_stage;

    if(old_layout == vk::ImageLayout::eUndefined
    && new_layout == vk::ImageLayout::eTransferDstOptimal){
        barrier.srcAccessMask = static_cast<vk::AccessFlagBits>(0);
        barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

        source_stage = vk::PipelineStageFlagBits::eTopOfPipe;
        destination_stage = vk::PipelineStageFlagBits::eTransfer;
    }else if(old_layout == vk::ImageLayout::eTransferDstOptimal &&
    new_layout == vk::ImageLayout::eShaderReadOnlyOptimal){
        barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
        barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

        source_stage = vk::PipelineStageFlagBits::eTransfer;
        destination_stage = vk::PipelineStageFlagBits::eFragmentShader;
    }else{
        throw std::invalid_argument("unsuported layout transition");
    }

    command->pipelineBarrier(
            source_stage, destination_stage,
            static_cast<vk::DependencyFlagBits>(0),
            0, nullptr,
            0, nullptr,
            1, &barrier);
    create_image_views(context);

}

void buffer::image2d::create_image_views(Context const &context) {
    _image_view = context.create_2d_image_views(*_image, vk::Format::eR8G8B8A8Srgb, vk::ImageAspectFlagBits::eColor);
}

