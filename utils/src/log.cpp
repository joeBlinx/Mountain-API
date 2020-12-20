//
// Created by joe on 05/08/18.
//

#include "log.hpp"
#include <stdexcept>
#include <string>
#include <map>
#define enumToStr(x) x, #x
std::map<int, std::string> VkResultStr{
   {enumToStr(VK_SUCCESS ) },
   {enumToStr(VK_NOT_READY) },
   {enumToStr(VK_TIMEOUT) },
   {enumToStr(VK_EVENT_SET ) },
   {enumToStr(VK_EVENT_RESET ) },
   {enumToStr(VK_INCOMPLETE ) },
   {enumToStr(VK_ERROR_OUT_OF_HOST_MEMORY ) },
   {enumToStr(VK_ERROR_OUT_OF_DEVICE_MEMORY ) },
   {enumToStr(VK_ERROR_INITIALIZATION_FAILED ) },
   {enumToStr(VK_ERROR_DEVICE_LOST ) },
   {enumToStr(VK_ERROR_MEMORY_MAP_FAILED ) },
   {enumToStr(VK_ERROR_LAYER_NOT_PRESENT ) },
   {enumToStr(VK_ERROR_EXTENSION_NOT_PRESENT ) },
   {enumToStr(VK_ERROR_FEATURE_NOT_PRESENT ) },
   {enumToStr(VK_ERROR_INCOMPATIBLE_DRIVER ) },
   {enumToStr(VK_ERROR_TOO_MANY_OBJECTS ) },
   {enumToStr(VK_ERROR_FORMAT_NOT_SUPPORTED ) },
   {enumToStr(VK_ERROR_FRAGMENTED_POOL ) },
   {enumToStr(VK_ERROR_SURFACE_LOST_KHR ) },
   {enumToStr(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR ) },
   {enumToStr(VK_SUBOPTIMAL_KHR ) },
   {enumToStr(VK_ERROR_OUT_OF_DATE_KHR ) },
   {enumToStr(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR ) },
   {enumToStr(VK_ERROR_VALIDATION_FAILED_EXT ) },
   {enumToStr(VK_ERROR_INVALID_SHADER_NV ) },
   {enumToStr(VK_ERROR_OUT_OF_POOL_MEMORY_KHR ) },
   {enumToStr(VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR ) },
   {enumToStr(VK_RESULT_BEGIN_RANGE ) },
   {enumToStr(VK_RESULT_END_RANGE ) },
   {enumToStr(VK_RESULT_RANGE_SIZE ) },
   {enumToStr(VK_RESULT_MAX_ENUM ) }
};
void checkError(VkResult result, const std::string& log){
	if(result != VK_SUCCESS){
		throw std::runtime_error(log + "\n error is:" + VkResultStr[result]);
	}
}

#undef enumToStr