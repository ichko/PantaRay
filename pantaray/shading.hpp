#pragma once

#include "color.hpp"
#include "ray.hpp"
#include "object.hpp"

namespace PantaRay {

    struct IShader {

        virtual Color Shade(const Ray& ray, Intersection& intersection) = 0;

        virtual ~IShader() {}

    };

    struct Checker : public IShader {

        double size;

        Color first;
        Color second;

        Checker(Color& _first, Color& _second, double _size = 5) :
            size(_size), first(_first), second(_second) {
        }

        Color Shade(const Ray& ray, Intersection& intersection) {
            int x = (int) float(intersection.u / size);
            int y = (int) float(intersection.v / size);

            return (x + y) % 2 == 0 ? first : second;
        }

    };

}