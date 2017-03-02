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

    struct LambertShader : public IShader {

        Color Shade(ShadingContext& context);

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
