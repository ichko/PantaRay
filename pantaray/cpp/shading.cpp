#include "../hpp/shading.hpp"


namespace PantaRay {

    Color NormalShader::Shade(Ray& ray, Intersection& intersection, ITexture* texture, std::vector<ILight*>& lights) {
        auto r = float(intersection.normal.x);
        auto g = float(intersection.normal.y);
        auto b = float(intersection.normal.z);

        return Color(fabs(r), fabs(g), fabs(b));
    }

    Color LambertShader::Shade(Ray& ray, Intersection& intersection, ITexture* texture, std::vector<ILight*>& lights) {
        Color color_sum;
        Color color = Color::White();

        if (texture != nullptr) {
            color = texture->Sample(intersection);
        }

        for (auto& light : lights) {
            if (light->IsType(LightType::Point)) {
                auto point_light = Cast<PointLight*>(light);
                auto vector_to_light = point_light->position.Copy().Subtract(intersection.position);
                auto light_factor = vector_to_light.Copy().Normalize().Dot(intersection.normal);
                auto attenuation = 1.0f / vector_to_light.LengthSqr();
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

    Color CopositionShader::Shade(Ray& ray, Intersection& intersection, ITexture* texture, std::vector<ILight*>& lights) {
        auto first_color = first->Shade(ray, intersection, texture, lights).Scale(ratio);
        auto second_color = second->Shade(ray, intersection, texture, lights).Scale(1 - ratio);

        return first_color.Add(second_color);
    }

}
