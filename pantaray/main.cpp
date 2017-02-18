#include "pantaray.hpp"
using namespace PantaRay;
using namespace PantaRay::Constants;

int main() {

    auto width = 600;
    auto height = 800;

    auto camera = PinholåCamera(pi / 2 , width / height);
    auto renderer = Renderer(width, height);

    renderer.Render(camera);

}