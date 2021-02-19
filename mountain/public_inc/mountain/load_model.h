//
// Created by stiven_perso on 1/10/21.
//

#ifndef MOUNTAIN_API_LOAD_MODEL_H
#define MOUNTAIN_API_LOAD_MODEL_H

#include <filesystem>
#include "vertex.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace mountain::model{
    namespace fs = std::filesystem;
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    struct Vertex{
        glm::vec3 pos{};
        glm::vec2 tex_coord{};

        bool operator==(const Vertex& other) const {
            return pos == other.pos && tex_coord == other.tex_coord;
        }
        static auto get_format_offsets() {
            return mountain::get_format_offsets(&Vertex::pos, &Vertex::tex_coord);
        }
    };
#endif
    /**
     *
     * @param model_path: path to the obj to load
     * @return a vector of vertices and a vector of the corresponding indices
     */
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> load_obj(fs::path const& model_path);
}

#endif //MOUNTAIN_API_LOAD_MODEL_H
