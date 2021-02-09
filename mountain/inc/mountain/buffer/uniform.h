//
// Created by stiven_perso on 12/19/20.
//

#ifndef MOUNTAIN_API_UNIFORM_H
#define MOUNTAIN_API_UNIFORM_H

#include "mountain/swapChain.h"
#include "utils/raii_helper.h"
#include <memory>
namespace mountain::buffer {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        struct uniform_updater {
            uniform_updater(std::vector<vk::UniqueDeviceMemory> &memories, std::byte *data, size_t data_size);

            void operator()(Context const &context, int current_image);

        private:
            struct Free {
                void operator()(std::byte *foo) {
                    free(foo);
                }
            };

            std::unique_ptr<std::byte, Free> _data;
            vk::DeviceSize _buffer_size;
            std::vector<vk::UniqueDeviceMemory> &_memories;
        };
#endif
        /**
         *  The uniform class in Mountain-API packed two vulkan things:
         *  - vk::Buffer
         *  - vk::MemoryDevice
         *  It's purpose is to encapsulate the creation of this two things.
         * @tparam T: type of the value we want in our uniform
         */
        template<class T>
        struct uniform{
#ifndef DOXYGEN_SHOULD_SKIP_THIS
            using iterator = std::vector<vk::UniqueBuffer>::iterator;
            using const_iterator = std::vector<vk::UniqueBuffer>::const_iterator;
#endif
            /**
             * Construct a uniform object
             * @param context: Vulkan context
             * @param swap_chain_nb_images: nb of uniform to create, one for each swap chain image
             */
            uniform(Context const &context, size_t swap_chain_nb_images);

            /**
             *
             * @param value: value for this uniform
             * @return an uniform_updater object, it has to be passed to the draw function of
             * CommandBuffer to be effective
             */
            uniform_updater get_uniform_updater(const T &value);
#ifndef DOXYGEN_SHOULD_SKIP_THIS

            iterator begin() { return std::begin(_buffers); }

            iterator end() { return std::end(_buffers); }

            const_iterator begin() const { return std::begin(_buffers); }

            const_iterator end() const { return std::end(_buffers); }

            auto size() const {
                return _buffers.size();
            }
#endif
        private:
            std::vector<vk::UniqueDeviceMemory> _buffer_memories;
            std::vector<vk::UniqueBuffer> _buffers;
            Context const &_device;
            vk::DeviceSize _buffer_size;
        };

        template<class T>
        uniform<T>::uniform(Context const &context, size_t swap_chain_nb_images):_device(context),
                                                                                 _buffer_size(sizeof(T)) {

            _buffers.reserve(swap_chain_nb_images);
            _buffer_memories.reserve(swap_chain_nb_images);

            for (size_t i = 0; i < swap_chain_nb_images; i++) {
                auto[buffer_memory, buffer] =
                context.create_buffer_and_memory(_buffer_size,
                                                 vk::BufferUsageFlagBits::eUniformBuffer,
                                                 vk::MemoryPropertyFlagBits::eHostVisible |
                                                 vk::MemoryPropertyFlagBits::eHostCoherent);

                _buffers.emplace_back(std::move(buffer));
                _buffer_memories.emplace_back(std::move(buffer_memory));
            }
        }

        template<class T>
        uniform_updater uniform<T>::get_uniform_updater(const T &value) {
            return {_buffer_memories,
                    reinterpret_cast<std::byte *>(
                            const_cast<T *>(&value)),
                    sizeof(T)};

        }
}


#endif //MOUNTAIN_API_UNIFORM_H
