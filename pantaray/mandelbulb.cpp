#include <SDL.h>
#include <time.h>
#include <math.h>

#include "hpp/pantaray.hpp"
#include "hpp/sdl-init.hpp"

using namespace PantaRay;
using namespace PantaRay::Constants;

int main(int argc, char** argv) {
    unsigned width = 450;
    unsigned height = 450;

    auto renderer = Renderer(width, height, Color(0.01f, 0.01f, 0.01f));
    renderer.anti_aliasing = true;

    auto camera = PinholeCamera(pi / 2.5f, float(width) / float(height))
        .Set(Vector(0, -2, 0), Vector(0, 0, 0));

    auto mandelbulb_geometry = DistanceEstimatorGeometry([](Vector p) -> float {
        Vector z = p;
        float power = 17.0f;
        float dr = 1.0f;
        float r = 0.0f;

        for (size_t i = 0; i < 4; i++) {
            r = z.Length();
            if (r > 10) break;

            float theta = acos(z.z / r);
            float phi = atan2(z.y, z.x);
            dr = float(pow(r, power - 1.0f) * power * dr + 1.0f);

            float zr = pow(r, power);
            theta = theta * power;
            phi = phi * power;

            z = Vector(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta))
                .Scale(zr)
                .Add(p);
        }

        return float(0.5 * log(r) * r / dr);
    });

    auto distance_shader = DistanceShader();


    auto point_light_left = PointLight(Vector(-15, 20, 20), 550);

    auto scene = Scene()
        .Add(Mesh(mandelbulb_geometry, distance_shader))
        .Add(point_light_left);

    clock_t tStart = clock();

    auto buffer = renderer.Render(camera, scene);

    printf("Time taken: %.6fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    init(width, height, buffer);

    return 0;
}