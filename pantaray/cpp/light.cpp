#include "../hpp/shading-context.hpp"
#include "../hpp/light.hpp"


namespace PantaRay {

    float ILight::GetLightContribution(ShadingContext& context) {
        return intensity;
    }

    float PointLight::GetLightContribution(ShadingContext& context) {
        auto distance_to_light = position.Copy().Subtract(context.intersection->position).LengthSqr();
        return intensity / distance_to_light;
    }

}