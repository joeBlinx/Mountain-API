//
// Created by joe on 05/08/18.
//

#ifndef MOUNTAIN_API_LOG_HPP
#define MOUNTAIN_API_LOG_HPP

#include <vulkan/vulkan.hpp>
#include <iosfwd>
#include <string>
#include <map>
#include "mountain/mountainapi_export.h"
extern std::map<int, std::string> VkResultStr;

MOUNTAINAPI_EXPORT void checkError(VkResult result,  std::string const& log);
inline void checkError(vk::Result result,  std::string const& log){
    checkError(static_cast<VkResult>(result), log);
}

template<class T>
void checkError(T const& , const std::string& ){

}



#endif //MOUNTAIN_API_LOG_HPP
