//
// Created by stiven_perso on 1/10/21.
//

#ifndef SANDBOX_LOAD_MODEL_H
#define SANDBOX_LOAD_MODEL_H

#include <filesystem>
#include "buffer/vertex.hpp"
namespace model{
    namespace fs = std::filesystem;
    struct Vertex{
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 tex_coord;

        static std::vector<format_offset<Vertex>> get_format_offset(){
            return CLASS_DESCRIPTION(
                    Vertex, pos, color, tex_coord
                    );
        }
    };
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> load_obj(fs::path const& model_path);
}
#endif //SANDBOX_LOAD_MODEL_H
