#pragma once


#include "color.hpp"

namespace PantaRay {

    struct ITexture {

        virtual void Set(unsigned x, unsigned y, Color color) {}

        virtual Color Sample(unsigned x, unsigned y) const = 0;

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

        Color Sample(unsigned x, unsigned y) const {
            return data[y * width + x];
        }


        ~Image() {
            delete[] data;
        }

    };

}