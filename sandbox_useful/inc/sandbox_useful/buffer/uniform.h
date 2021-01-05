//
// Created by stiven_perso on 12/19/20.
//

#ifndef SANDBOX_UNIFORM_H
#define SANDBOX_UNIFORM_H

#include "sandbox_useful/swapChain.hpp"
#include "utils/raii_helper.h"
#include <memory>
namespace buffer{
    struct uniform_updater{
        uniform_updater(std::vector<vk::UniqueDeviceMemory> &memories, std::byte *data, size_t data_size);
        void operator()(Context const& context, int current_image);
    private:
        struct Free{
            void operator()(std::byte* foo){
                free(foo);
            }
        };
        std::unique_ptr<std::byte, Free> _data;
        vk::DeviceSize _buffer_size;
        std::vector<vk::UniqueDeviceMemory> & _memories;
    };
    template<class T>
    struct uniform{
        using iterator = std::vector<vk::UniqueBuffer>::iterator;
        using const_iterator = std::vector<vk::UniqueBuffer>::const_iterator;
        uniform(Context const &context, size_t swap_chain_nb_images);
        uniform_updater get_uniform_updater(const T &value);
        iterator begin(){return std::begin(_buffers);}
        iterator end(){return std::end(_buffers);}
        const_iterator begin() const{return std::begin(_buffers);}
        const_iterator end() const{return std::end(_buffers);}

        int size() const{
            return _buffers.size();
        }

    private:
        std::vector<vk::UniqueBuffer> _buffers;
        std::vector<vk::UniqueDeviceMemory> _buffer_memories;
        Context const& _device;
        vk::DeviceSize _buffer_size;
    };
    template<class T>
    uniform<T>::uniform(Context const &context, size_t swap_chain_nb_images):_device(context),
    _buffer_size(sizeof(T)){

        _buffers.reserve(swap_chain_nb_images);
        _buffer_memories.reserve(swap_chain_nb_images);

        for (size_t i = 0; i < swap_chain_nb_images; i++) {
            auto[buffer, buffer_memory] =
                    context.create_buffer_and_memory(_buffer_size,
                                                    vk::BufferUsageFlagBits::eUniformBuffer,
                                                    vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);

            _buffers.emplace_back(std::move(buffer));
            _buffer_memories.emplace_back(std::move(buffer_memory));
        }
    }

    template<class T>
    uniform_updater uniform<T>::get_uniform_updater(const T &value)  {
        return {_buffer_memories,
                reinterpret_cast<std::byte *>(
                        const_cast<T*>(&value)),
                sizeof(T)};

    }
}


#endif //SANDBOX_UNIFORM_H
