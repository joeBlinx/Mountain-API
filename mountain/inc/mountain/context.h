#ifndef BASIC_INIT_HPP
#define BASIC_INIT_HPP

#include <vector>
#include <vulkan/vulkan.hpp>
#include <string_view>
#include "window.h"
struct GLFWwindow;
namespace mountain {
        /**
         * Context class will hold the Vulkan context and so will be necessary to all other classes
         */
    struct Context {
#ifndef DOXYGEN_SHOULD_SKIP_THIS

            struct QueueFamilyIndices {
            static int constexpr number_queue = 1;
            int graphics_family = -1;
            int present_family = -1;

            bool is_complete() {
                return graphics_family >= 0 && present_family >= 0;
            }
        };

        struct SwapChainSupportDetails {
            vk::SurfaceCapabilitiesKHR capabilities;
            std::vector<vk::SurfaceFormatKHR> formats;
            std::vector<vk::PresentModeKHR> presentModes;
        };
#endif
        /**
         *
         * @param window: The window we want to us
         * @param devicesExtension : extensions we need. Example : VK_KHR_SWAPCHAIN_EXTENSION_NAME
         */
        Context(Window const& window, std::vector<const char *> const &devicesExtension);

        Context(int width, int height, std::string_view title, std::vector<const char *> const &devicesExtension);

        Context(Context const &) = delete;

        Context &operator=(Context const &) = delete;

        ~Context();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        VkSurfaceKHR get_vk_surface() const { return _surface; }

        const vk::Queue &get_graphics_queue() const { return _graphics_queue; }

        const vk::Queue &get_present_queue() const { return _present_queue; }

        vk::PhysicalDevice const &get_physical_device() const { return _physical_device; }

        QueueFamilyIndices const &get_queue_family_indice() const { return _indices; }

        SwapChainSupportDetails const &get_swap_chain_details() const { return _swap_chain_details; }

        vk::CommandPool const &get_command_pool() const { return _command_pool; }

        vk::Device const &get_device() const { return _device; }

#endif
        /**
         *
         * @return Window object
         */
        Window const &get_window() const { return _window; }

        /**
         * Useful to use vk::Device method through Context object
         * @return The vulkan device
         */
        vk::Device const &operator*() const { return get_device(); }
        /**
         * Useful to use vk::Device method through Context object
         * @return The vulkan device
         */
        vk::Device const *operator->() const { return &get_device(); }

        /**
         * Helper function which create a buffer and it's associated memory
         *
         * @param size: Size of the buffer
         * @param usage: Usage of the buffer. example: eHostCoherent
         * @param properties: Properties that we want for the memories. example: eTransferDst
         */
        [[nodiscard]] std::pair<vk::UniqueDeviceMemory, vk::UniqueBuffer>
        create_buffer_and_memory(vk::DeviceSize const &size, vk::BufferUsageFlags usage,
                                 vk::MemoryPropertyFlags properties) const;
        /**
         * Copy a fixed size content of source into destination
         * @param destination
         * @param source
         * @param size: Fixed size data to copied
         */
        void
        copy_buffer(vk::UniqueBuffer &destination, vk::UniqueBuffer const &source, vk::DeviceSize const &size) const;

        /**
         * Copy the content of buffer inside image
         * @param buffer
         * @param image
         * @param width: width of the image
         * @param height: height of the image
         */
        void copy_buffer_to_image(vk::Buffer buffer, vk::Image image, uint32_t width, uint32_t height) const;

        /**
         * Create a 2d Image view from an Image
         * @param image: The image you'd want to create image view from
         * @param format: Format of the image view
         * @param aspectFlags:
         * @param mipmap_levels: mipmap level of the image
         * @return ImageView with automatic resource managment
         */
        [[nodiscard]] vk::UniqueImageView
        create_2d_image_views(vk::Image image, const vk::Format &format, vk::ImageAspectFlags aspectFlags,
                              uint32_t mipmap_levels) const;
        /**
         * Create an image and it's associated memory
         * @param width
         * @param height
         * @param format
         * @param tiling: eOptimal or eLinear. Linear -> you have direct access to texel. Optimal: optimise for speed
         * @param usage: usage of memory. example eTransferDst
         * @param mipmap_levels: level of mipmap you'll be using
         * @return Image and memory with automatic resources management
         */
        [[nodiscard]] std::pair<vk::UniqueImage, vk::UniqueDeviceMemory>
        create_image(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling,
                     const vk::ImageUsageFlags &usage, vk::MemoryPropertyFlagBits, uint32_t mipmap_levels) const;

        /**
         *
         * @return adequate swap chain format
         */
        vk::SurfaceFormatKHR choose_swap_surface_format() const;

    private:
        std::vector<const char *> const _validationLayers = {
                "VK_LAYER_KHRONOS_validation"
        };
#ifdef NDEBUG
        static bool constexpr _enableValidationLayer = false;
#else
        static bool constexpr _enableValidationLayer = true;
#endif
        Window const& _window;
        vk::Instance _instance;
        VkSurfaceKHR _surface;

        VkDebugReportCallbackEXT _callback;
        vk::PhysicalDevice _physical_device;
        vk::Device _device;
        vk::CommandPool _command_pool;
        vk::Queue _graphics_queue;
        vk::Queue _present_queue;

        QueueFamilyIndices _indices;

        SwapChainSupportDetails _swap_chain_details;

        void pick_up_physical_device(vk::Instance instance, vk::QueueFlagBits queue_flag,
                                     std::vector<const char *> const &devicesExtension,
                                     VkSurfaceKHR surface);

        void create_logical_device(std::vector<char const *> const &devicesExtension,
                                   std::vector<const char *> const &validationLayers);

        void create_command_pool();

        bool checkValidationLayerSupport();

        std::vector<char const *> getRequiredExtension();

        void createInstance(std::string_view title);

        void createSurface();

        void setUpDebugCallBack();

        [[nodiscard]] vk::UniqueDeviceMemory
        create_device_memory(vk::MemoryRequirements const &mem_requirements, vk::MemoryPropertyFlags type_filter) const;

        vk::Instance const &get_vk_instance() const { return _instance; }


        };
}
#endif
