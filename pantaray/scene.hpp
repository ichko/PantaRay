#pragma once

#include <vector>

#include "mesh.hpp"
#include "light.hpp"

namespace PantaRay {

    class Scene {

        std::vector<Mesh> objects;
        std::vector<ILight*> lights;

    public:
        Scene& Add(Mesh&& mesh) {
            objects.push_back(mesh);
            return *this;
        }

        Scene& Add(ILight& light) {
            lights.push_back(&light);
            return *this;
        }

        std::vector<Mesh>& GetObjects() {
            return objects;
        }

        std::vector<ILight*>& GetLights() {
            return lights;
        }

    };

}