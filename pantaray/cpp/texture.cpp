#include "../hpp/texture.hpp"


namespace PantaRay {

    Color CheckerTexture::Sample(const Intersection& intersection) const {
        int x = (int)floor(intersection.u / size);
        int y = (int)floor(intersection.v / size);

        return (x + y) % 2 == 0 ? first : second;
    }

    Color NormalTexture::Sample(const Intersection& intersection) const {
        float r = float(fabs(intersection.normal.x));
        float g = float(fabs(intersection.normal.y));
        float b = float(fabs(intersection.normal.z));

        return Color(r, g, b);
    }

}
