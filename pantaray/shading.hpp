#pragma once

#include "color.hpp"
#include "ray.hpp"
#include "intersection.hpp"

namespace PantaRay {

    struct IShader {

        virtual Color Shade(Ray& ray, Intersection& intersection) = 0;

        virtual ~IShader() {}

    };

    struct CheckerShader : public IShader {

        double size;

        Color first;
        Color second;

        CheckerShader(Color&& _first, Color&& _second, double _size = 2000000) :
            size(_size), first(_first), second(_second) {
        }

        Color Shade(Ray& ray, Intersection& intersection) {
            int x = (int) double(intersection.u / size);
            int y = (int) double(intersection.v / size);

            return (x + y) % 2 == 0 ? first : second;
        }

    };

    struct NormalShader : public IShader {

        Color Shade(Ray& ray, Intersection& intersection) {
            auto normal = intersection.normal.Copy();
            normal.x = fabs(normal.x);
            normal.y = fabs(normal.y);
            normal.z = fabs(normal.z);

            return Color(normal.x, normal.y, normal.z);
        }

    };

}