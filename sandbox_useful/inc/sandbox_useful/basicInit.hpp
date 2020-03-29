#ifndef BASIC_INIT_HPP
#define BASIC_INIT_HPP

#include <vector>
#include <vulkan/vulkan.hpp>
#include <string_view>
struct GLFWwindow;
struct BasicInit
{

	BasicInit(int width, int height, std::string_view title);
	BasicInit(BasicInit const&) = delete;
    BasicInit& operator=(BasicInit const&) = delete;
	~BasicInit();
	vk::Instance const& get_vk_instance() const{return _instance;}
	VkSurfaceKHR get_vk_surface() const{return _surface;}
	GLFWwindow * get_window() {return _window;}

private:
	 std::vector<const char*> const _validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
	};
#ifdef NDEBUG
	 static bool constexpr _enableValidationLayer = false;
#else
	 static bool constexpr _enableValidationLayer = true;
#endif

	GLFWwindow * _window;
	unsigned _width, _height;
	vk::Instance _instance;
	VkSurfaceKHR _surface;
	
	VkDebugReportCallbackEXT _callback;

	void initWindow(std::string_view title);
	bool checkValidationLayerSupport();
	std::vector<char const * > getRequiredExtension();
	void createInstance(std::string_view title);
	void createSurface();
	void setUpDebugCallBack();

};
#endif
