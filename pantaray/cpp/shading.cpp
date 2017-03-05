#include <math.h>
#include "../hpp/shading.hpp"


namespace PantaRay {

    float ShadowCoefficient(ShadingContext& context, PointLight* light, float in_shadow_coefficient = 0.1) {
        auto start_position = context.intersection->position.Copy()
            .Add(context.intersection->normal.Copy().Scale(Constants::eps));
        auto target_dist = start_position.Copy().Subtract(light->position).Length();
        auto shado_coefficient = 1.0f;
        Intersection intersection;

        context.scene->Intersect(Ray(
            start_position,
            light->position.Copy().Subtract(context.intersection->position).Normalize()
        ), intersection);

        if (intersection.mesh != nullptr && intersection.distance < target_dist) {
            shado_coefficient = in_shadow_coefficient;
        }

        return shado_coefficient;
    }

    Color NormalShader::Shade(ShadingContext& context) {
        auto r = float(context.intersection->normal.x);
        auto g = float(context.intersection->normal.y);
        auto b = float(context.intersection->normal.z);

        return Color(fabs(r), fabs(g), fabs(b));
    }

    Color DistanceShader::Shade(ShadingContext& context) {
        auto color = context.intersection->distance;
        return Color(color, color, color);
    }

    Color PhongShader::Shade(ShadingContext& context) {
        Color color_sum;
        Color color = Color::White();

        if (context.texture != nullptr) {
            color = context.texture->Sample(*context.intersection);
        }

        for (auto& light : context.scene->GetLights()) {
            if (light->IsType(LightType::Point)) {
                auto point_light = Cast<PointLight*>(light);
                auto vector_to_light = point_light->position.Copy().Subtract(context.intersection->position);
                auto lambert_coefficient = vector_to_light.Copy().Normalize().Dot(context.intersection->normal);
                auto light_factor = point_light->intensity / vector_to_light.LengthSqr();

                auto vector_from_ligh = context.intersection->position.Copy().Subtract(point_light->position);
                auto reflected_vector = vector_from_ligh.Normalize().Reflect(context.intersection->normal);
                auto phong_coefficient = float(fmax(0.0f, context.ray->direction.Copy().Invert().Dot(reflected_vector)));
                phong_coefficient = float(pow(phong_coefficient, specular_exponent));

                auto shadow_coefficient = ShadowCoefficient(context, point_light);

                color_sum
                    .Legalize()
                    .Add(point_light->color.Copy().Scale(lambert_coefficient * light_factor * shadow_coefficient))
                    .Add(Color::White().Scale(phong_coefficient * specular_multiplier * light_factor * shadow_coefficient))
                    .Times(color);
            }
            else if (light->IsType(LightType::Ambient)) {
                auto ambient_light = Cast<AmbientLight*>(light);
                color_sum.Legalize().Add(color.Copy().Times(ambient_light->color));
            }
        }

        return color_sum;
    }

    Color CopositionShader::Shade(ShadingContext& context) {
        auto first_color = first->Shade(context).Scale(ratio);
        auto second_color = second->Shade(context).Scale(1 - ratio);

        return first_color.Add(second_color);
    }


    Color ReflectionShader::Shade(ShadingContext& context) {
        Color result = Color::White();
        if (context.texture != nullptr) {
            result = context.texture->Sample(*context.intersection);
        }

        if (context.ray->recursion_depth < max_recursion_depth) {
            Ray reflection_ray(
                context.intersection->position.Copy().Add(context.ray->direction.Copy().Scale(Constants::eps)),
                context.ray->direction.Copy().Reflect(context.intersection->normal).Normalize()
            );
            reflection_ray.recursion_depth = context.ray->recursion_depth + 1;

            Color reflected_ray_color = Renderer::Trace(reflection_ray, *context.scene);
            result.Times(reflected_ray_color.Scale(reflection_damping));
        }

        return result;
    }

}
