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

        Color& Times(const Color& color) {
            r *= color.r;
            g *= color.g;
            b *= color.b;

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

        Color& Legalize() {
            r = fminf(fmax(0.f, r), 1.f);
            g = fminf(fmax(0.f, g), 1.f);
            b = fminf(fmax(0.f, b), 1.f);

            return *this;
        }

        static Color White() {
            return Color(1, 1, 1);
        }

    };

}