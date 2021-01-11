//
// Created by stiven_perso on 1/10/21.
//

#include <glm/glm.hpp>
#include "load_model.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace model{
    static const std::vector<glm::vec3> g_vertex_buffer_data {
            {-1.0f,-1.0f,-1.0f}, // triangle 1 : begi}n
             {-1.0f,-1.0f, 1.0f},
              {-1.0f, 1.0f, 1.0f}, // triangle 1 : en}d
               {1.0f, 1.0f,-1.0f}, // triangle 2 : begi}n
                {-1.0f,-1.0f,-1.0f},
                 {-1.0f, 1.0f,-1.0f}, // triangle 2 : en}d
                  {1.0f,-1.0f, 1.0f},
                   {-1.0f,-1.0f,-1.0f},
                    {1.0f,-1.0f,-1.0f},
                     {1.0f, 1.0f,-1.0f},
                      {1.0f,-1.0f,-1.0f},
                       {-1.0f,-1.0f,-1.0f},
                        {-1.0f,-1.0f,-1.0f},
                         {-1.0f, 1.0f, 1.0f},
                          {-1.0f, 1.0f,-1.0f},
                           {1.0f,-1.0f, 1.0f},
                            {-1.0f,-1.0f, 1.0f},
                             {-1.0f,-1.0f,-1.0f},
                              {-1.0f, 1.0f, 1.0f},
                               {-1.0f,-1.0f, 1.0f},
                                {1.0f,-1.0f, 1.0f},
                                 {1.0f, 1.0f, 1.0f},
                                  {1.0f,-1.0f,-1.0f},
                                   {1.0f, 1.0f,-1.0f},
                                    {1.0f,-1.0f,-1.0f},
                                     {1.0f, 1.0f, 1.0f},
                                      {1.0f,-1.0f, 1.0f},
                                       {1.0f, 1.0f, 1.0f},
                                        {1.0f, 1.0f,-1.0f},
                                         {-1.0f, 1.0f,-1.0f},
                                          {1.0f, 1.0f, 1.0f},
                                           {-1.0f, 1.0f,-1.0f},
                                            {-1.0f, 1.0f, 1.0f},
                                             {1.0f, 1.0f, 1.0f},
                                              {-1.0f, 1.0f, 1.0f},
                                               {1.0f,-1.0f, 1.0f}
    };
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> load_obj(fs::path const& model_path){
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string err;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, model_path.c_str())) {
            throw std::runtime_error(err);
        }
        for(auto& shape: shapes){
            for(auto &index : shape.mesh.indices){
                indices.push_back(indices.size());
                vertices.emplace_back(Vertex{
                    .pos{
                            attrib.vertices[3 * index.vertex_index + 0],
                            attrib.vertices[3 * index.vertex_index + 1],
                            attrib.vertices[3 * index.vertex_index + 2]
                    },
                    .color{1.0f, 1.0f, 1.0f},
                    .tex_coord{
                            attrib.texcoords[2 * index.texcoord_index + 0],
                            attrib.texcoords[2 * index.texcoord_index + 1]
                    }
                });
            }
        }
        vertices.clear();
        indices.clear();
        int i = 0;
        for(auto &vertex : g_vertex_buffer_data){
            indices.emplace_back(indices.size());
            vertices.emplace_back(
                    Vertex{
                        .pos = vertex,
                        .color {1.0f, 1.0f, 1.0f},
                        .tex_coord{1.0f, 1.0f}
                    }
                    );
            if(i++ >=11){
                break;
            }
        }

        return {vertices, indices};
    }
}