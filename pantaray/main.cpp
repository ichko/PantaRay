#include <SDL.h>

#include "pantaray.hpp"
#include "sdl.hpp"

using namespace PantaRay;
using namespace PantaRay::Constants;

int main(int argc, char** argv) {

    auto width = 800;
    auto height = 600;

    auto renderer = Renderer(width, height);
    auto camera = PinholåCamera(pi / 2, width / height)
        .Setup(Vector(0, 0, 30), Vector(0, 1, 30));

    auto plane_geometry = PlaneGeometry(Vector(), Vector(0, 0, 1));
    auto sphere_geometry = SphereGeometry(Vector(30, 80, 30), 20);

    auto checker_shader = CheckerShader(Color(1, 1, 0), Color(0, 1, 0));
    auto sphere_checker_shader = CheckerShader(Color(1, 1, 1), Color(0, 1, 0), 0.0001);

    auto scene = Scene()
        .Add(Mesh(plane_geometry, checker_shader))
        .Add(Mesh(sphere_geometry, sphere_checker_shader));

    auto buffer = renderer.Render(camera, scene);

    magic(width, height, buffer);

    return 0;

}