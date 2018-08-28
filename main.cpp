#include <iostream>
#include "initVulkan.hpp"

int main() {
	InitVulkan init(1366, 768);

	init.loop();
	return 0;
}