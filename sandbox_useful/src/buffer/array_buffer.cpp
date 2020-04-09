#include "array_buffer.hpp"
#include "device.hpp"
namespace buffer{
	vertex::vertex(Device const& device):_device(device.get_device())
	{
		vk::BufferCreateInfo create_info;
		create_info.size = 1;
		create_info.usage = vk::BufferUsageFlagBits::eVertexBuffer;
		create_info.sharingMode = vk::SharingMode::eExclusive;
		_buffer = _device.createBufferUnique(create_info);
		
	}
}