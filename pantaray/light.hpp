#pragma once

#include "color.hpp"
#include "vector.hpp"
#include "intersection.hpp"

namespace PantaRay {

    struct ILight {

        double intensity;
        Color color;

        virtual Vector CastOn(const Vector& intersection_position) = 0;

        virtual ~ILight() {}

    };

    struct PointLight : public ILight {

        Vector position;

        PointLight(const Vector&& _position, double _intensity = 1, Color& _color = Color::White()) : position(_position) {
            intensity = _intensity;
            color = _color;
        }

        Vector CastOn(const Vector& intersection_position) {
            return intersection_position.Copy().Subtract(position).Normalize();
        };

    };

}