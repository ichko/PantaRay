#include "../hpp/renderer.hpp"


namespace PantaRay {

    Image* Renderer::Render(ICamera& camera, Scene& scene) {
        camera.Begin();

        for (unsigned y = 0; y < height; ++y) {
            for (unsigned x = 0; x < width; ++x) {
                float x_interpolate = float(x) / float(width);
                float y_interpolate = float(y) / float(height);

                if (anti_aliasing) {
                    float kernel_size = 2.0f;
                    Color color_sum = Color();
                    for (float i = 0; i < kernel_size; ++i) {
                        for (float j = 0; j < kernel_size; ++j) {
                            Ray ray = camera
                                .GetRay(x_interpolate + ((i / kernel_size) / width),
                                        y_interpolate + ((j / kernel_size) / height));

                            color_sum.Add(Trace(ray, scene));
                        }
                    }

                    screen_buffer.Set(x, y, color_sum.Scale(1.0f / (kernel_size * kernel_size)));
                }
                else {
                    Ray ray = camera.GetRay(x_interpolate, y_interpolate);
                    screen_buffer.Set(x, y, Trace(ray, scene));
                }
            }
        }

        return &screen_buffer;
    }

    Color Renderer::Trace(Ray& ray, Scene& scene) {
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
            ShadingContext context(ray, closest_intersection, closest_mesh->texture, scene);
            return closest_mesh->shader->Shade(context);
        }

        return background;
    }

}
