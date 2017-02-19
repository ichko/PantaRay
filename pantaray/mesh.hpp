#pragma once

#include "geometry.hpp"
#include "shading.hpp"


namespace PantaRay {

    struct Mesh {

        IGeometry* geometry;
        IShader* shader;

        Mesh(IGeometry* _geometry, IShader* _shader) : geometry(_geometry), shader(_shader) {}

    };

}