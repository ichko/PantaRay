#pragma once

#include "color.hpp"
#include "camera.hpp"
#include "scene.hpp"

namespace PantaRay {

    class Renderer {

        unsigned width;
        unsigned height;

        Color** screen_buffer;
        Color background;

    public:
        Renderer(unsigned _width, unsigned _height, Color&& _background = Color()) :
            width(_width),
            height(_height),
            background(_background) {
            screen_buffer = new Color*[height];
            for (unsigned y = 0; y < height; y++) {
                screen_buffer[y] = new Color[width];
            }
        }

        ~Renderer() {
            for (unsigned y = 0; y < height; y++) {
                delete[] screen_buffer[y];
            }
            delete[] screen_buffer;
        }

        Color** Render(ICamera& camera, Scene& scene) {
            camera.Begin();

            for (unsigned y = 0; y < height; ++y) {
                for (unsigned x = 0; x < width; x++) {
                    double x_interpolate = double(x) / double(width);
                    double y_interpolate = double(y) / double(height);
                    Ray ray = camera.GetRay(x_interpolate, y_interpolate);
                    screen_buffer[y][x] = Trace(ray, scene);
                }
            }

            return screen_buffer;
        }

    private:
        Color Trace(Ray& ray, Scene& scene) {
            auto closest_intersection = Intersection();
            closest_intersection.distance = Constants::inf;
            Mesh* closest_mesh = nullptr;

            for (auto& object : scene.GetObjects()) {
                auto intersection = Intersection();
                if (object.geometry->Intersect(ray, intersection) &&
                    intersection.distance < closest_intersection.distance) {
                    closest_intersection = intersection;
                    closest_mesh = &object;
                }
            }

            if (closest_mesh != nullptr) {
                return closest_mesh->shader->Shade(ray, closest_intersection);
            }

            return background;
        }

    };

}