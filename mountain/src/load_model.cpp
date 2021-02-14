//
// Created by stiven_perso on 1/10/21.
//

#include <glm/glm.hpp>
#include "../public_inc/mountain/load_model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <unordered_map>
namespace std {
    template<> struct hash<mountain::model::Vertex> {
        size_t operator()(mountain::model::Vertex const& vertex) const {
            return (hash<glm::vec3>()(vertex.pos) ^
                    (hash<glm::vec2>()(vertex.tex_coord) << 1));
        }
    };
}
namespace mountain::model{
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> load_obj(fs::path const& model_path){
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string err;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, model_path.string().c_str())) {
            throw std::runtime_error(err);
        }
        std::unordered_map<Vertex, uint32_t> unique_vertices;
        for(auto& shape: shapes){
            for(auto &index : shape.mesh.indices){
                Vertex vertex{
                        .pos{
                                attrib.vertices[3 * index.vertex_index + 0],
                                attrib.vertices[3 * index.vertex_index + 1],
                                attrib.vertices[3 * index.vertex_index + 2]
                        },
                        .tex_coord{
                                attrib.texcoords[2 * index.texcoord_index + 0],
                                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                        }
                };
                if (unique_vertices.count(vertex) == 0) {
                    unique_vertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(unique_vertices[vertex]);

            }
        }

        return {vertices, indices};
    }
}