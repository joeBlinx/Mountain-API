//
// Created by stiven_perso on 1/10/21.
//

#ifndef SANDBOX_LOAD_MODEL_H
#define SANDBOX_LOAD_MODEL_H

#include <filesystem>
#include "buffer/vertex.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace mountain::model{
    namespace fs = std::filesystem;
    struct Vertex{
        glm::vec3 pos{};
        glm::vec2 tex_coord{};

        bool operator==(const Vertex& other) const {
            return pos == other.pos && tex_coord == other.tex_coord;
        }
        static decltype(auto) get_format_offset(){
            return CLASS_DESCRIPTION(
                    Vertex, pos, tex_coord
                    );
        }
    };
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> load_obj(fs::path const& model_path);
}
namespace std {
    template<> struct hash<mountain::model::Vertex> {
        size_t operator()(mountain::model::Vertex const& vertex) const {
            return (hash<glm::vec3>()(vertex.pos) ^
                   (hash<glm::vec2>()(vertex.tex_coord) << 1));
        }
    };
}
#endif //SANDBOX_LOAD_MODEL_H
