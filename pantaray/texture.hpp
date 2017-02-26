#pragma once


#include "color.hpp"

namespace PantaRay {

    struct ITexture {

        virtual void Set(unsigned x, unsigned y, Color color) {}

        virtual Color Sample(float u, float v) const = 0;

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

        Color Sample(float u, float v) const {
            int x = (int)floor(u / size);
            int y = (int)floor(v / size);

            return (x + y) % 2 == 0 ? first : second;
        }

    };

    struct SolidColorTexture : ITexture {

        Color color;

        SolidColorTexture(Color _color) : color(_color) {}

        Color Sample(float u, float v) const {
            return color;
        }

    };

}