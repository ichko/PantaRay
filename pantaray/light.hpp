#pragma once

#include "color.hpp"
#include "vector.hpp"
#include "intersection.hpp"

namespace PantaRay {

    enum LightType {
        Point,
        Ambient
    };

    struct ILight {

        float intensity;
        Color color;
        LightType type;

        virtual Vector VectorToLight(const Vector& intersection_position) = 0;

        virtual ~ILight() {}

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

        Vector VectorToLight(const Vector& intersection_position) {
            return position.Copy().Subtract(intersection_position);
        };

    };

    struct AmbientLight : public ILight {

        Vector position;

        AmbientLight(Color _color) {
            color = _color;
            type = LightType::Ambient;
        }

        Vector VectorToLight(const Vector& intersection_position) {
            return Vector();
        };

    };

}