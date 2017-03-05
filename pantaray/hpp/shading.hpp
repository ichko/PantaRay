#pragma once

#include <vector>

#include "shading-context.hpp"
#include "texture.hpp"
#include "light.hpp"
#include "utils.hpp"
#include "ray.hpp"
#include "renderer.hpp"


namespace PantaRay {

    struct IShader {

        virtual Color Shade(ShadingContext& context) = 0;

        virtual ~IShader() {}

    };

    struct NormalShader : public IShader {

        Color Shade(ShadingContext& context);

    };

    struct PhongShader : public IShader {

        float specular_multiplier;
        float specular_exponent;

        PhongShader(const float&& _specular_multiplier = 0.0f, const float&& _specular_exponent = 8.0f) :
            specular_multiplier(_specular_multiplier), specular_exponent(_specular_exponent) {
        }

        virtual Color Shade(ShadingContext& context);

    };

    struct DistanceShader : public IShader {

        Color Shade(ShadingContext& context);

    };

    struct CopositionShader : public IShader {

        IShader* first;
        IShader* second;
        float ratio;

        CopositionShader(IShader& _first, IShader& _second, float _ratio = 0.5) :
            first(&_first), second(&_second), ratio(_ratio) {
        }

        Color Shade(ShadingContext& context);

    };

    struct ReflectionShader : public IShader {

        float reflection_damping;

        ReflectionShader(float _reflection_damping = 1) :
            reflection_damping(_reflection_damping) {
        }

        Color Shade(ShadingContext& context);

    };

}
