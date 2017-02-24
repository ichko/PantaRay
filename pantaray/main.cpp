#include <SDL.h>

#include "pantaray.hpp"
#include "sdl-init.hpp"

using namespace PantaRay;
using namespace PantaRay::Constants;

int main(int argc, char** argv) {

    auto width = 800;
    auto height = 600;

    auto renderer = Renderer(width, height);

    auto camera = PinholeCamera(pi / 2, width / height)
        .Set(Vector(10, 0, 20), Vector(10, -1, 20), Vector(0, 0, 1));

    auto plane_geometry = PlaneGeometry(Vector(0, 0, 0), Vector(0, 0, 1));
    auto sphere_geometry = SphereGeometry(Vector(30, -50, 30), 20);

    auto checker_shader = CheckerShader(Color(1, 1, 0), Color(0, 1, 0));
    auto sphere_checker_shader = CheckerShader(Color(1, 0, 0), Color(0, 0, 1), 0.0001);
    auto normal_shader = NormalShader();

    auto scene = Scene()
        .Add(Mesh(plane_geometry, checker_shader))
        .Add(Mesh(sphere_geometry, normal_shader));

    auto buffer = renderer.Render(camera, scene);

    magic(width, height, buffer);

    return 0;

}