#include <iostream>
#include "../include/initVulkan.hpp"
#include "../sandbox_useful/basicInit.hpp"

int main() {
	BasicInit basic_init{1366, 768, "test"};
//	InitVulkan init(1366, 768);
	InitVulkan init(basic_init.get_vk_instance()
			, basic_init.get_vk_surface());


	init.loop(basic_init.get_window());

	return 0;
}