#pragma once


#include "intersection.hpp"
#include "color.hpp"

namespace PantaRay {

    struct ITexture {

        virtual void Set(unsigned x, unsigned y, Color color) {}

        virtual Color Sample(float u, float v) const { return Color(); };

        virtual Color Sample(const Intersection& intersection) const { return Color(); };

        virtual ~ITexture() {}

    };

    struct Image : public ITexture {

        unsigned width;
        unsigned height;
        Color* data;

        Image(unsigned _width, unsigned _height) :
            width(_width), height(_height),
            data(new Color[width * height]) {
        }

        void Set(unsigned x, unsigned y, Color color) {
            data[y * width + x] = color;
        }

        Color Sample(float u, float v) const {
            return data[int(v) * width + int(u)];
        }


        ~Image() {
            delete[] data;
        }

    };



    struct CheckerTexture : public ITexture {

        float size;

        Color first;
        Color second;

        CheckerTexture(Color&& _first, Color&& _second, float _size = 5) :
            size(_size), first(_first), second(_second) {
        }

        Color Sample(const Intersection& intersection) const {
            int x = (int)floor(intersection.u / size);
            int y = (int)floor(intersection.v / size);

            return (x + y) % 2 == 0 ? first : second;
        }

    };

    struct SolidColorTexture : ITexture {

        Color color;

        SolidColorTexture(Color _color) : color(_color) {}

        Color Sample(const Intersection& intersection) const {
            return color;
        }

    };

    struct NormalTexture : ITexture {

        Color Sample(const Intersection& intersection) const {
            float r = float(fabs(intersection.normal.x));
            float g = float(fabs(intersection.normal.y));
            float b = float(fabs(intersection.normal.z));

            return Color(r, g, b);
        }

    };

}