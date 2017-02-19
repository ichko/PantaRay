#include <iostream>
#include "pantaray.hpp"
using namespace PantaRay;
using namespace PantaRay::Constants;

int main() {

    auto width = 80;
    auto height = 25;

    auto renderer = Renderer(width, height);
    auto camera = PinholåCamera(pi / 2, width / height)
        .Setup(Vector(0, 0, 10), Vector(0, 1, 10));

    auto plane_geometry = PlaneGeometry(Vector(), Vector(0, 0, 1));
    auto checker_shader = CheckerShader(Color(1, 1, 0), Color(0, 1, 0));

    auto scene = Scene().Add(Mesh(&plane_geometry, &checker_shader));

    auto buffer = renderer.Render(camera, scene);

    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            char symbol = '_';
            if (buffer[y][x].g > 0) {
                symbol = '#';
            }
            if (buffer[y][x].r > 0) {
                symbol = '-';
            }

            std::cout << symbol;
        }
        std::cout << std::endl;
    }

}