#pragma once

#include "color.hpp"
#include "vector.hpp"
#include "intersection.hpp"

namespace PantaRay {

    struct ShadingContext;

    enum LightType {
        Point,
        Ambient
    };

    struct ILight {

        float intensity;
        Color color;
        LightType type;

        virtual ~ILight() {}

        virtual float GetLightContribution(ShadingContext& context);

        bool IsType(LightType _type) {
            return type == _type;
        }

    };

    struct PointLight : public ILight {

        Vector position;

        PointLight(const Vector&& _position, float _intensity = 1, Color& _color = Color::White()) : position(_position) {
            intensity = _intensity;
            color = _color;
            type = LightType::Point;
        }

        float GetLightContribution(ShadingContext& context);

    };

    struct AmbientLight : public ILight {

        Vector position;

        AmbientLight(Color _color) {
            color = _color;
            type = LightType::Ambient;
        }

        float GetLightContribution(ShadingContext& context) {
            return 1.0f;
        };

    };

}
