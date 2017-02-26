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
            int x = (int) floor(intersection.u / size);
            int y = (int) floor(intersection.v / size);

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
                if (light->IsType(LightType::Point)) {
                    auto point_light = Cast<PointLight*>(light);
                    auto vector_to_light = point_light->VectorToLight(intersection.position);
                    auto light_factor = vector_to_light.Copy().Normalize().Dot(intersection.normal);
                    auto attenuation = 1.0 / vector_to_light.LengthSqr();
                    color_sum
                        .Legalize()
                        .Add(point_light->color.Copy().Scale(light_factor * attenuation * point_light->intensity))
                        .Times(color);
                }
                else if (light->IsType(LightType::Ambient)) {
                    auto ambient_light = Cast<AmbientLight*>(light);
                    color_sum.Legalize().Add(color.Copy().Times(ambient_light->color));
                }
            }

            return color_sum;
        }

    };

    struct CopositionShader : public IShader {

        IShader* first;
        IShader* second;
        float ratio;

        CopositionShader(IShader& _first, IShader& _second, float _ratio = 0.5) :
            first(&_first), second(&_second), ratio(_ratio) {}

        Color Shade(Ray& ray, Intersection& intersection, std::vector<ILight*>& lights) {
            auto first_color = first->Shade(ray, intersection, lights).Scale(ratio);
            auto second_color = second->Shade(ray, intersection, lights).Scale(1 - ratio);

            return first_color.Add(second_color);
        }

    };

}