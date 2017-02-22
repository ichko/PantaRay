#pragma once

#include "constants.hpp"

namespace PantaRay {

    struct Color {

        float r, g, b;

        Color(float _r = 0, float _g = 0, float _b = 0) : r(_r), g(_g), b(_b) {}

        Color& Scale(float scale) {
            r *= scale;
            g *= scale;
            b *= scale;

            return *this;
        }

        Color& Add(const Color& color) {
            r += color.r;
            g += color.g;
            b += color.b;

            return *this;
        }

        Color Copy() {
            return Color(r, g, b);
        }

    };

}