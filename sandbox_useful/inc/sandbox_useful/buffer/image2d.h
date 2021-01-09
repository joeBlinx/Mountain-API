//
// Created by stiven_perso on 1/5/21.
//

#ifndef SANDBOX_IMAGE2D_H
#define SANDBOX_IMAGE2D_H
#include <vulkan/vulkan.hpp>
#include <filesystem>
#include "sandbox_useful/context.hpp"

namespace buffer {
    namespace fs = std::filesystem;

    struct image2d {

        image2d(Context const &context, fs::path const &image_path);
        vk::UniqueImage const& get_image()const{return _image;}
        vk::UniqueImageView const& get_image_view()const{return _image_view;}
    private:
        vk::UniqueDeviceMemory _image_memory;
        vk::UniqueImage _image;
        vk::UniqueImageView  _image_view;

        void transition_image_layout(Context const &context, vk::Format format, vk::ImageLayout old_layout,
                                     vk::ImageLayout new_layout);
        void create_image_views(Context const &context);

    };
}
#endif //SANDBOX_IMAGE2D_H
