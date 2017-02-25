#pragma once

#include <vector>

#include "intersection.hpp"
#include "light.hpp"
#include "color.hpp"
#include "utils.hpp"
#include "ray.hpp"

namespace PantaRay {

    struct IShader {

        virtual Color Shade(Ray& ray, Intersection& intersection, std::vector<ILight*>& lights) = 0;

        virtual ~IShader() {}

    };

    struct CheckerShader : public IShader {

        float size;

        Color first;
        Color second;

        CheckerShader(Color&& _first, Color&& _second, float _size = 5) :
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
            auto r = float(intersection.normal.x);
            auto g = float(intersection.normal.y);
            auto b = float(intersection.normal.z);

            return Color(fabs(r), fabs(g), fabs(b));
        }

    };

    struct LambertShader : public IShader {

        Color color;

        LambertShader(Color&& _color) : color(_color) {}

        Color Shade(Ray& ray, Intersection& intersection, std::vector<ILight*>& lights) {
            Color color_sum;

            for (auto& light : lights) {
                if (light->IsType(LightType::PointLigh)) {
                    auto point_light = Cast<PointLight*>(light);
                    auto light_factor = point_light->CastOn(intersection.position).Dot(intersection.normal);
                    color_sum.Add(point_light->color.Copy().Scale(float(light_factor)));
                }
            }

            return color_sum.Times(color);
        }

    };

}