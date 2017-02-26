#pragma once

#include "ray.hpp"
#include "intersection.hpp"
#include "texture.hpp"
#include "scene.hpp"


namespace PantaRay {

    struct ShadingContext {

        Ray* ray;
        Intersection* intersection;
        ITexture* texture;
        Scene* scene;

        ShadingContext(Ray& _ray, Intersection& _intersection, ITexture* _texture, Scene& _scene) :
            ray(&_ray), intersection(&_intersection), texture(_texture), scene(&_scene) {}

    };

}