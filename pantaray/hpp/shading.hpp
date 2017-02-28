#pragma once

#include <vector>

#include "texture.hpp"
#include "light.hpp"
#include "utils.hpp"
#include "ray.hpp"


namespace PantaRay {

    struct IShader {

        virtual Color Shade(Ray& ray, Intersection& intersection, ITexture* texture, std::vector<ILight*>& lights) = 0;

        virtual ~IShader() {}

    };

    struct NormalShader : public IShader {

        Color Shade(Ray& ray, Intersection& intersection, ITexture* texture, std::vector<ILight*>& lights);

    };

    struct LambertShader : public IShader {

        Color Shade(Ray& ray, Intersection& intersection, ITexture* texture, std::vector<ILight*>& lights);

    };

    struct CopositionShader : public IShader {

        IShader* first;
        IShader* second;
        float ratio;

        CopositionShader(IShader& _first, IShader& _second, float _ratio = 0.5) :
            first(&_first), second(&_second), ratio(_ratio) {}

        Color Shade(Ray& ray, Intersection& intersection, ITexture* texture, std::vector<ILight*>& lights);

    };

}
