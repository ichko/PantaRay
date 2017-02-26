#include <SDL.h>
#include <time.h>

#include "pantaray.hpp"
#include "sdl-init.hpp"

using namespace PantaRay;
using namespace PantaRay::Constants;

int main(int argc, char** argv) {

    unsigned width = 500;
    unsigned height = 500;

    auto renderer = Renderer(width, height, Color(0.01f, 0.01f, 0.01f));
    renderer.anti_aliasing = true;

    auto camera = PinholeCamera(pi / 2.5f, float(width) / float(height))
        .Set(Vector(10, 0, 20), Vector(10, 1, 20), Vector(0, 0, 1));

    auto plane_geometry_top = PlaneGeometry(Vector(0, 0, 0), Vector(0, 0, 1));
    auto plane_geometry_bottom = PlaneGeometry(Vector(0, 0, 60), Vector(0, 0, -1));
    auto plane_geometry_left = PlaneGeometry(Vector(-20, 0, 0), Vector(1, 0, 0));
    auto plane_geometry_back = PlaneGeometry(Vector(0, 100, 0), Vector(0, -1, 0));
    auto plane_geometry_right = PlaneGeometry(Vector(50, 0, 0), Vector(-1, 0, 0));


    auto sphere_geometry = SphereGeometry(Vector(35, 80, 30), 20);
    auto sphere_geometry_small = SphereGeometry(Vector(12, 75, 30), 12);
    auto sphere_geometry_big = SphereGeometry(Vector(-10, 75, 0), 25);

    auto checker_shader = CheckerShader(Color(0.8f, 0.8f, 0.8f), Color(0.1f, 0.1f, 0.1f));
    auto sphere_checker_shader = CheckerShader(Color(1, 0, 0), Color(0, 0, 1), 0.01f);
    auto normal_shader = NormalShader();

    auto lambert_shader_red = LambertShader(Color(1, 0, 0));
    auto lambert_shader = LambertShader(Color(1, 1, 1));

    auto composed_shader = CopositionShader(checker_shader, lambert_shader_red);

    auto point_light_red = PointLight(Vector(10, 40, 25), 550, Color(1, 0, 0));
    auto point_light_green = PointLight(Vector(15, 40, 40), 500, Color(0, 1, 0));
    auto point_light_blue = PointLight(Vector(30, 40, 30), 500, Color(0, 0, 1));
    auto point_light_big = PointLight(Vector(30, 80, 55), 400, Color(1, 1, 1));

    auto ambient_light = AmbientLight(Color(0.01f, 0.01f, 0.01f));

    auto scene = Scene()
        .Add(Mesh(plane_geometry_top, composed_shader))
        .Add(Mesh(plane_geometry_bottom, composed_shader))
        .Add(Mesh(plane_geometry_left, lambert_shader_red))
        .Add(Mesh(plane_geometry_back, lambert_shader_red))
        .Add(Mesh(plane_geometry_right, lambert_shader_red))

        .Add(Mesh(sphere_geometry, lambert_shader))
        .Add(Mesh(sphere_geometry_small, lambert_shader))
        .Add(Mesh(sphere_geometry_big, lambert_shader))

        .Add(point_light_red)
        .Add(point_light_green)
        .Add(point_light_blue)
        //.Add(point_light_big)

        .Add(ambient_light);

    clock_t tStart = clock();

    auto buffer = renderer.Render(camera, scene);

    printf("Time taken: %.6fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    init(width, height, buffer);

    return 0;

}