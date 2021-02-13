#include "context.h"
#include "utils/utils.hpp"
#include <string_view>
#include "utils/log.hpp"
#include <iostream>
#include <cstring>
#include <string_view>
#include <set>
#include <uniform.h>
#include "no_sanitize.h"
namespace mountain {

    Context::SwapChainSupportDetails query_swap_chain_support(vk::PhysicalDevice const &device, VkSurfaceKHR surface);

    Context::QueueFamilyIndices
    find_queue_families(vk::PhysicalDevice const &device, VkSurfaceKHR surface, vk::QueueFlagBits queue_flag);
    Context::Context(const Window &window, std::vector<const char *> const &devicesExtension): _window(window) {
        createInstance(window.get_title());
        createSurface();
        setUpDebugCallBack();

        auto queue_flag = vk::QueueFlagBits::eGraphics;

        auto const &surface = get_vk_surface();
        pick_up_physical_device(get_vk_instance(), queue_flag, devicesExtension, surface);

        _swap_chain_details = query_swap_chain_support(_physical_device, surface);
        _indices = find_queue_families(_physical_device, surface, queue_flag);

        create_logical_device(devicesExtension, _validationLayers);
        create_command_pool();
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            [[maybe_unused]] VkDebugReportFlagsEXT flags,
            [[maybe_unused]] VkDebugReportObjectTypeEXT objType,
            [[maybe_unused]] uint64_t obj,
            [[maybe_unused]] size_t location,
            [[maybe_unused]] int32_t code,
            [[maybe_unused]] const char *layerPrefix,
            const char *msg,
            [[maybe_unused]] void *userData) {

        std::cerr << "validation layer: " << msg << std::endl;

        return VK_FALSE;
    }

    std::vector<char const *> Context::getRequiredExtension() {
        std::vector<const char *> extensions(_window.get_instance_extension());

        if (_enableValidationLayer) {
            extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        }

        return extensions;
    }

    void DestroyDebugReportCallbackEXT(vk::Instance instance, VkDebugReportCallbackEXT callback,
                                       const VkAllocationCallbacks *pAllocator) {
        auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                                "vkDestroyDebugReportCallbackEXT");
        if (func != nullptr) {
            func(instance, callback, pAllocator);
        }
    }

    Context::~Context() {

        _device.destroy(_command_pool);
        _device.destroy();
        if constexpr (_enableValidationLayer) {
            DestroyDebugReportCallbackEXT(_instance, _callback, nullptr);
        }
        _instance.destroy(_surface);
        _instance.destroy();
    }


    bool Context::checkValidationLayerSupport() {

        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayer(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayer.data());
        bool layerFound = false;
        for (auto layer : _validationLayers) {
            for (auto available : availableLayer) {
                std::string test(available.layerName);
                utils::print(available.layerName);
                if (!strcmp(layer, available.layerName)) {
                    layerFound = true;
                    break;
                }
            }
        }
        return layerFound;

    }

    VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugReportCallbackEXT *pCallback) {
        auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                               "vkCreateDebugReportCallbackEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pCallback);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Context::setUpDebugCallBack() {

        if constexpr (!_enableValidationLayer) return;

        VkDebugReportCallbackCreateInfoEXT info{};
        info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        info.pfnCallback = debugCallback;
        info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

        checkError(CreateDebugReportCallbackEXT(_instance, &info, nullptr, &_callback),
                   "Failed to set up debug _callback");
    }

    void Context::createInstance(std::string_view title) {
        if (!checkValidationLayerSupport() && _enableValidationLayer) {
            utils::printFatalError("validation layer requested but not available");

        }

        vk::ApplicationInfo info{};
        info.pApplicationName = title.data();
        info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        info.pEngineName = "No Engine";
        info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        info.apiVersion = VK_API_VERSION_1_0;

        vk::InstanceCreateInfo instanceinfo{};
        instanceinfo.pApplicationInfo = &info;

        std::vector<const char *> extensions(getRequiredExtension());
        instanceinfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instanceinfo.ppEnabledExtensionNames = extensions.data();

        instanceinfo.enabledLayerCount = 0;

        VkValidationFeatureEnableEXT enables[] = {VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT};
        VkValidationFeaturesEXT features = {};
        features.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
        features.enabledValidationFeatureCount = 1;
        features.pEnabledValidationFeatures = enables;

        if constexpr(_enableValidationLayer) {
            instanceinfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
            instanceinfo.ppEnabledLayerNames = _validationLayers.data();
            instanceinfo.pNext = &features;
        }
        _instance = vk::createInstance(instanceinfo);
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionsProperties(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsProperties.data());

        if constexpr (_enableValidationLayer) {
            utils::print("available extensions:");
            for (const auto &extension : extensionsProperties) {
                utils::print("\t", extension.extensionName);
            }
        }
    }

    void Context::createSurface() {
        checkError(create_window_surface(_instance,
                                         _window, nullptr, &_surface),
                   "unable to create surface");
    }


    Context::QueueFamilyIndices
    find_queue_families(vk::PhysicalDevice const &device, VkSurfaceKHR surface, vk::QueueFlagBits queue_flag) {
        Context::QueueFamilyIndices indices;
        auto queueFamilies = device.getQueueFamilyProperties();
        uint32_t i = 0;

        for (const auto &queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & queue_flag) {
                indices.graphics_family = i;
            }

            vk::Bool32 presentSupport = device.getSurfaceSupportKHR(i, surface);
            if (queueFamily.queueCount > 0 && presentSupport) {
                indices.present_family = i;
            }
            if (indices.is_complete()) {
                break;

            }

            i++;
        }

        return indices;
    }

    Context::SwapChainSupportDetails query_swap_chain_support(vk::PhysicalDevice const &device, VkSurfaceKHR surface) {
        Context::SwapChainSupportDetails details;
        details.capabilities = device.getSurfaceCapabilitiesKHR(surface);
        details.formats = device.getSurfaceFormatsKHR(surface);
        details.presentModes = device.getSurfacePresentModesKHR(surface);

        return details;
    }

    bool check_device_extension_support(vk::PhysicalDevice const &device,
                                        std::vector<const char *> const &devicesExtension) {

        auto availableExtensions = device.enumerateDeviceExtensionProperties();
        std::set<std::string_view> requiredExtensions{devicesExtension.begin(), devicesExtension.end()};

        for (auto const &extension : availableExtensions) {
            requiredExtensions.erase(std::string_view(extension.extensionName));
        }
        return requiredExtensions.empty();
    }

    bool is_device_suitable(vk::PhysicalDevice const &device, vk::QueueFlagBits queue_flag,
                            std::vector<const char *> const &devicesExtension, VkSurfaceKHR surface) {
        Context::QueueFamilyIndices indices = find_queue_families(device, surface, queue_flag);

        bool extensionSupported = check_device_extension_support(device, devicesExtension);
        bool swapChainAdequate = false;
        if (extensionSupported) {
            Context::SwapChainSupportDetails swapChainSupport = query_swap_chain_support(device, surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }
        vk::PhysicalDeviceFeatures supported_features;
        device.getFeatures(&supported_features);
        return indices.is_complete() && extensionSupported && swapChainAdequate && supported_features.samplerAnisotropy;
    }

    int get_point_to_device_type(vk::PhysicalDeviceType device_type) {
        switch (device_type) {
            case vk::PhysicalDeviceType::eOther:
                return 0;
            case vk::PhysicalDeviceType::eCpu:
                return 1;
            case vk::PhysicalDeviceType::eVirtualGpu:
                return 2;
            case vk::PhysicalDeviceType::eIntegratedGpu:
                return 3;
            case vk::PhysicalDeviceType::eDiscreteGpu:
                return 4;
        }
        return 0;
    }

    void Context::pick_up_physical_device(vk::Instance instance, vk::QueueFlagBits queue_flag,
                                          std::vector<const char *> const &devicesExtension,
                                          VkSurfaceKHR surface) {

        auto physicalDevices = instance.enumeratePhysicalDevices();
        if (physicalDevices.empty()) {
            utils::printFatalError("failed to find gpu with vulkan support");
        }
        struct RankGpu {
            vk::PhysicalDevice device;
            int rank{};

            bool operator>(RankGpu const &a) const {
                return rank > a.rank;
            }
        };
        std::set<RankGpu, std::greater<>> physical_available;
        for (auto device : physicalDevices) {
            if (is_device_suitable(device, queue_flag, devicesExtension, surface)) {
                vk::PhysicalDeviceProperties prop;
                device.getProperties(&prop);
                physical_available.insert(
                        RankGpu{
                                device,
                                get_point_to_device_type(prop.deviceType)
                        }
                );
            }
        }
        if (!physical_available.empty()) {
            _physical_device = physical_available.begin()->device;
            return;
        }
        utils::printFatalError("no suitable GPU found");
    }

    NO_SANITIZE
    void Context::create_logical_device(std::vector<char const *> const &devicesExtension,
                                        std::vector<const char *> const &validationLayers) {

        //specify the queue
        std::vector<vk::DeviceQueueCreateInfo> queueInfos;
        std::set<int> uniqueQueueFamilies{_indices.graphics_family, _indices.present_family};
        for (auto queue : uniqueQueueFamilies) {
            vk::DeviceQueueCreateInfo queueInfo{};
            queueInfo.queueFamilyIndex = static_cast<uint32_t>(queue);
            queueInfo.queueCount = QueueFamilyIndices::number_queue;
            float queuePriority = 1.0f;
            queueInfo.pQueuePriorities = &queuePriority;
            queueInfos.push_back(queueInfo);
        }
        //feature required
        vk::PhysicalDeviceFeatures features{};
        features.samplerAnisotropy = VK_TRUE;
        vk::DeviceCreateInfo info{};
        info.setPQueueCreateInfos(queueInfos.data());
        info.queueCreateInfoCount = (uint32_t) queueInfos.size();
        info.pEnabledFeatures = &features;
        info.enabledExtensionCount = static_cast<uint32_t>(devicesExtension.size());
        info.ppEnabledExtensionNames = devicesExtension.data();
        if constexpr(utils::debug) {
            info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            info.ppEnabledLayerNames = validationLayers.data();
        }

        _device = _physical_device.createDevice(info);
        _graphics_queue = _device.getQueue(_indices.graphics_family, 0);
        _present_queue = _device.getQueue(_indices.present_family, 0);
    }

    void Context::create_command_pool() {
        vk::CommandPoolCreateInfo pool_info{
                vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
                static_cast<uint32_t>(_indices.graphics_family)
        };
        _command_pool = _device.createCommandPool(pool_info);
    }

    std::pair<vk::UniqueDeviceMemory, vk::UniqueBuffer>
    Context::create_buffer_and_memory(vk::DeviceSize const &size, vk::BufferUsageFlags usage,
                                      vk::MemoryPropertyFlags properties) const {
        vk::BufferCreateInfo buffer_info{
                {},
                size,
                usage,
                vk::SharingMode::eExclusive
        };
        vk::UniqueBuffer buffer = _device.createBufferUnique(buffer_info);

        vk::MemoryRequirements mem_requirement;
        _device.getBufferMemoryRequirements(*buffer, &mem_requirement);
        auto device_memory = create_device_memory(mem_requirement, properties);
        _device.bindBufferMemory(*buffer, *device_memory, 0);
        return {
                std::move(device_memory),
                std::move(buffer)
        };
    }

    vk::UniqueDeviceMemory Context::create_device_memory(vk::MemoryRequirements const &mem_requirements,
                                                         vk::MemoryPropertyFlags properties) const {
        auto mem_properties = _physical_device.getMemoryProperties();

        auto find_memory_type = [&mem_properties, type_filter = mem_requirements.memoryTypeBits, &properties]() {
            for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++) {
                if ((type_filter & (1 << i)) &&
                    (mem_properties.memoryTypes[i].propertyFlags & properties) == properties) {
                    return i;
                }
            }
            utils::printFatalError("failed to find suitable memory type!");
            return 0u;
        };
        return _device.allocateMemoryUnique(
                vk::MemoryAllocateInfo(
                        mem_requirements.size,
                        find_memory_type()
                )
        );
    }

    void Context::copy_buffer(vk::UniqueBuffer &destination, vk::UniqueBuffer const &source,
                              vk::DeviceSize const &size) const {

        utils::raii_helper::OneTimeCommands commands(*this);
        vk::BufferCopy buffer_copy{
                0,
                0,
                size
        };
        commands->copyBuffer(*source, *destination, 1, &buffer_copy);
    }

    void Context::copy_buffer_to_image(vk::Buffer buffer, vk::Image image, uint32_t width, uint32_t height) const {

        utils::raii_helper::OneTimeCommands command(*this);
        vk::BufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;

        region.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;

        region.imageOffset = vk::Offset3D{0, 0, 0};
        region.imageExtent = vk::Extent3D{
                width,
                height,
                1
        };

        command->copyBufferToImage(
                buffer, image,
                vk::ImageLayout::eTransferDstOptimal,
                1, &region
        );
    }

    vk::UniqueImageView
    Context::create_2d_image_views(vk::Image image, const vk::Format &format, vk::ImageAspectFlags aspectFlags,
                                   uint32_t mipmap_levels) const {
        vk::ImageViewCreateInfo view_info{};
        view_info.image = image;
        view_info.viewType = vk::ImageViewType::e2D;
        view_info.format = format;
        view_info.subresourceRange.aspectMask = aspectFlags;
        view_info.subresourceRange.baseMipLevel = 0;
        view_info.subresourceRange.levelCount = mipmap_levels;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount = 1;

        return _device.createImageViewUnique(view_info);
    }

    std::pair<vk::UniqueImage, vk::UniqueDeviceMemory>
    Context::create_image(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling,
                          const vk::ImageUsageFlags &usage, vk::MemoryPropertyFlagBits, uint32_t mipmap_levels) const {
        vk::UniqueImage image;
        vk::UniqueDeviceMemory image_memory;
        vk::ImageCreateInfo image_info;
        image_info.imageType = vk::ImageType::e2D;
        image_info.extent.width = width;
        image_info.extent.height = height;
        image_info.extent.depth = 1;
        image_info.mipLevels = mipmap_levels;
        image_info.arrayLayers = 1;
        image_info.format = format;
        image_info.tiling = tiling;
        image_info.initialLayout = vk::ImageLayout::eUndefined;
        image_info.usage = usage;
        image_info.sharingMode = vk::SharingMode::eExclusive;
        image_info.samples = vk::SampleCountFlagBits::e1; // TODO: for multisampling

        image = get_device().createImageUnique(image_info);

        vk::MemoryRequirements requirements;
        get_device().getImageMemoryRequirements(*image, &requirements);
        image_memory = create_device_memory(
                requirements, vk::MemoryPropertyFlagBits::eDeviceLocal);

        get_device().bindImageMemory(*image, *image_memory, 0);
        return {std::move(image), std::move(image_memory)};
    }

    vk::SurfaceFormatKHR Context::choose_swap_surface_format() const {
        auto const &available_formats = _swap_chain_details.formats;
        if (available_formats.size() == 1 && available_formats[0].format == vk::Format::eUndefined) {
            return {vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear};
        }

        for (const auto &availableFormat : available_formats) {
            if (availableFormat.format == vk::Format::eB8G8R8A8Srgb &&
                availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                return availableFormat;
            }
        }

        return available_formats[0];
    }


}