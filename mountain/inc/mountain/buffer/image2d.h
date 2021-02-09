//
// Created by stiven_perso on 1/5/21.
//

#ifndef MOUNTAIN_API_IMAGE2D_H
#define MOUNTAIN_API_IMAGE2D_H
#include <vulkan/vulkan.hpp>
#include <filesystem>
#include "mountain/context.h"
#include <limits>
namespace mountain::buffer {
        namespace fs = std::filesystem;
        /**
         * A image2d in Mountain-API correspond to three vulkan things:
         * - vk::Image
         * - vk::MemoryDevice
         * - vk::ImageView
         * This three things are packed in this only structure. image2d will be required when you want to add
         * texture in your shaders
         */
        struct image2d {
            /**
             * Construct an image and it's associated Memory and imageview.
             * After the image2d has been construct, it can be use directly
             * @param context: Vulkan context
             * @param image_path: Path to the texture image
             * @param mipmap_level : mipmap level wanted (automatically compute)
             */
            image2d(Context const &context, fs::path const &image_path, uint32_t mipmap_level);
#ifndef DOXYGEN_SHOULD_SKIP_THIS
            vk::UniqueImage const &get_image() const { return _image; }

            vk::UniqueImageView const &get_image_view() const { return _image_view; }

            uint32_t get_mimap_levels() const { return _mipmap_levels; }
#endif

        private:

            static constexpr uint32_t max_mipmap = std::numeric_limits<uint32_t>::max();

            uint32_t _mipmap_levels;
            vk::UniqueDeviceMemory _image_memory;
            vk::UniqueImage _image;
            vk::UniqueImageView _image_view;

            void transition_image_layout(Context const &context, vk::ImageLayout old_layout,
                                         vk::ImageLayout new_layout);

            void create_image_views(Context const &context);

            void generate_mip_map(Context const &context, uint32_t tex_width, uint32_t tex_height);

        };
    }
#endif //MOUNTAIN_API_IMAGE2D_H
