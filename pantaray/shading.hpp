#pragma once

#include <vector>

#include "intersection.hpp"
#include "light.hpp"
#include "color.hpp"
#include "ray.hpp"

namespace PantaRay {

    struct IShader {

        virtual Color Shade(Ray& ray, Intersection& intersection, std::vector<ILight*>& lights) = 0;

        virtual ~IShader() {}

    };

    struct CheckerShader : public IShader {

        double size;

        Color first;
        Color second;

        CheckerShader(Color&& _first, Color&& _second, double _size = 5) :
            size(_size), first(_first), second(_second) {
        }

        Color Shade(Ray& ray, Intersection& intersection, std::vector<ILight*>& lights) {
            int x = int(intersection.u / size);
            int y = int(intersection.v / size);

            return (x + y) % 2 == 0 ? first : second;
        }

    };

    struct NormalShader : public IShader {

        Color Shade(Ray& ray, Intersection& intersection, std::vector<ILight*>& lights) {
            auto normal = intersection.normal;
            return Color(fabs(normal.x), fabs(normal.y), fabs(normal.z));
        }

    };

}