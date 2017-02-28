#pragma once

#include "color.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "texture.hpp"

namespace PantaRay {

    class Renderer {

        unsigned width;
        unsigned height;

        Image screen_buffer;
        Color background;

    public:
        bool anti_aliasing;

        Renderer(unsigned _width, unsigned _height, Color&& _background = Color()) :
            width(_width),
            height(_height),
            background(_background),
            screen_buffer(width, height),
            anti_aliasing(false) {
        }

        Image* Render(ICamera& camera, Scene& scene);

    private:
        Color Trace(Ray& ray, Scene& scene);

    };

}
