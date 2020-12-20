//
// Created by stiven_perso on 12/19/20.
//

#include <uniform.h>
#include "swapChain.hpp"

buffer::uniform_updater::uniform_updater(std::vector<vk::UniqueDeviceMemory> &memories, std::byte *data, size_t data_size):
_data(static_cast<std::byte*>(malloc(data_size))),
_buffer_size(data_size),
_memories(memories){

    memcpy(_data.get(), data, data_size);
}

void buffer::uniform_updater::operator()(const Context &context, int current_image) {

    auto vk_device = context.get_device();
    void* data{};
    utils::raii_helper::MapMemory raii_mapping(vk_device, _memories[current_image],
                                               0, _buffer_size, &data);
    memcpy(data, &*_data, static_cast<size_t>(_buffer_size));
}
