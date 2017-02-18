#pragma once

#include "color.hpp"
#include "camera.hpp"
#include "scene.hpp"

namespace PantaRay {

    class Renderer {

        unsigned width;
        unsigned height;

        Color** screen_buffer;

    public:
        Renderer(unsigned _width, unsigned _height) :
            width(_width),
            height(_height),
            screen_buffer((Color**) new Color[width * height]) {
        }

        ~Renderer() {
            delete[] screen_buffer;
        }

        Color** Render(ICamera& camera, IScene scene) {
            camera.Begin();

            for (unsigned y = 0; y < height; ++y) {
                for (unsigned x = 0; x < width; x++) {
                    double x_interpolate = double(x) / double(width);
                    double y_interpolate = double(y) / double(height);
                    Ray ray = camera.GetRay(x_interpolate, y_interpolate);
                }
            }

            return screen_buffer;
        }

    private:
        Color Trace(Ray& ray, const IScene& scene) {

        }


    };

}