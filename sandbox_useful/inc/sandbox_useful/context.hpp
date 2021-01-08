#ifndef BASIC_INIT_HPP
#define BASIC_INIT_HPP

#include <vector>
#include <vulkan/vulkan.hpp>
#include <string_view>
#include "window.h"
struct GLFWwindow;
struct Context
{
	struct QueueFamilyIndices{
		static int constexpr number_queue = 1;
		int graphics_family = -1;
		int present_family = -1;

		bool isComplete(){
			return graphics_family >=0  && present_family >= 0;
		}
	};
	struct SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector <vk::PresentModeKHR> presentModes;
	};
	Context(int width, int height, std::string_view title, std::vector<const char*> const& devicesExtension);
	Context(Context const&) = delete;
    Context& operator=(Context const&) = delete;
	~Context();
	vk::Instance const& get_vk_instance() const{return _instance;}
	VkSurfaceKHR get_vk_surface() const{return _surface;}
	Window const& get_window() const {return _window;}
	vk::Device const& get_device() const{ return _device; }
    vk::Device const& operator*() const{ return get_device();}
    vk::Device const* operator->() const{ return &get_device();}

    const vk::Queue & get_graphics_queue() const {return _graphics_queue;}
	const vk::Queue & get_present_queue() const{return _present_queue;}
	vk::PhysicalDevice const& get_physical_device() const{ return _physical_device;}
	QueueFamilyIndices const& get_queue_family_indice() const { return _indices; }
	SwapChainSupportDetails const& get_swap_chain_details() const { return _swap_chain_details; }
	vk::CommandPool const& get_command_pool() const{ return _command_pool; }
	vk::UniqueDeviceMemory create_device_memory(vk::MemoryRequirements const& mem_requirements, vk::MemoryPropertyFlags type_filter) const;
	std::pair<vk::UniqueBuffer,
		vk::UniqueDeviceMemory> create_buffer_and_memory(vk::DeviceSize const& size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties) const;

	void copy_buffer(vk::UniqueBuffer& destination, vk::UniqueBuffer const& source, vk::DeviceSize const& size) const;
    void copy_buffer_to_image(vk::Buffer buffer, vk::Image image, uint32_t width, uint32_t height)const;

    vk::UniqueImageView
    create_2d_image_views(vk::Image image, const vk::Format &format, vk::ImageAspectFlags aspectFlags) const;

    std::pair<vk::UniqueImage,vk::UniqueDeviceMemory>
    create_image(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, const vk::ImageUsageFlags &usage,
                 vk::MemoryPropertyFlagBits)const;

private:
	 std::vector<const char*> const _validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
	};
#ifdef NDEBUG
	 static bool constexpr _enableValidationLayer = false;
#else
	 static bool constexpr _enableValidationLayer = true;
#endif
    Window _window;
	vk::Instance _instance;
	VkSurfaceKHR _surface;
	
	VkDebugReportCallbackEXT _callback;
	vk::PhysicalDevice _physical_device;
	vk::Device _device;
	vk::CommandPool _command_pool;
	vk::Queue  _graphics_queue ;
	vk::Queue  _present_queue ;

	QueueFamilyIndices _indices;

	SwapChainSupportDetails _swap_chain_details;

	void pick_up_physical_device(vk::Instance instance, vk::QueueFlagBits queue_flag, std::vector<const char *> const &devicesExtension,
								 VkSurfaceKHR surface);
	void create_logical_device(std::vector<char const *> const &devicesExtension,
							   std::vector<const char *> const &validationLayers);
	void create_command_pool();

	bool checkValidationLayerSupport();
	std::vector<char const * > getRequiredExtension();
	void createInstance(std::string_view title);
	void createSurface();
	void setUpDebugCallBack();

};
#endif
