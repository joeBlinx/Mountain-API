//
// Created by stiven_perso on 1/10/21.
//

#ifndef SANDBOX_LOAD_MODEL_H
#define SANDBOX_LOAD_MODEL_H

#include <filesystem>
#include "buffer/vertex.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace model{
    namespace fs = std::filesystem;
    struct Vertex{
        glm::vec3 pos{};
        glm::vec3 color{};
        glm::vec2 tex_coord{};

        bool operator==(const Vertex& other) const {
            return pos == other.pos && color == other.color && tex_coord == other.tex_coord;
        }
        static std::vector<format_offset<Vertex>> get_format_offset(){
            return CLASS_DESCRIPTION(
                    Vertex, pos, color, tex_coord
                    );
        }
    };
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> load_obj(fs::path const& model_path);
}
namespace std {
    template<> struct hash<model::Vertex> {
        size_t operator()(model::Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^
                     (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.tex_coord) << 1);
        }
    };
}
#endif //SANDBOX_LOAD_MODEL_H
