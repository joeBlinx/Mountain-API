//
// Created by joe on 05/08/18.
//

#ifndef SANDBOX_LOG_HPP
#define SANDBOX_LOG_HPP

#include <vulkan/vulkan.h>
#include <iosfwd>
#include <string>
#include <map>
extern std::map<int, std::string> VkResultStr;

void checkError(VkResult result,  std::string const& log);
template<class T>
void checkError(T const& , const std::string& ){
	
}



#endif //SANDBOX_LOG_HPP
