#pragma once

#include "geometry.hpp"
#include "shading.hpp"
#include "texture.hpp"


namespace PantaRay {

    struct Mesh {

        IGeometry* geometry;
        IShader* shader;
        ITexture* texture;

        Mesh(IGeometry& _geometry, IShader& _shader) :
            geometry(&_geometry), shader(&_shader), texture(nullptr) {
        }

        Mesh(IGeometry& _geometry, IShader& _shader, ITexture& _texture) :
            geometry(&_geometry), shader(&_shader), texture(&_texture) {
        }

    };

}