//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_LOG_HPP
#define SANDBOX_LOG_HPP

#include <vulkan/vulkan.h>
#include <iosfwd>
#include <string>
void checkError(VkResult result, std::string log);



#endif //SANDBOX_LOG_HPP
