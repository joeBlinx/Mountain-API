//
// Created by stiven on 12/04/2020.
//
#include "mountain/vertex.h"
namespace mountain::buffer{
    void vertex::swap(vertex& v) {
        vertex temp;
        temp = std::move(v);
        v = std::move(*this);
        *this = std::move(temp);
    }
    void vertex::swap(vertex &&v) {
        swap(v);
    }
}
