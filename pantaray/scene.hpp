#pragma once

#include <vector>

#include "mesh.hpp"

namespace PantaRay {

    class Scene {

        std::vector<Mesh> objects;

    public:
        Scene& Add(Mesh&& mesh) {
            objects.push_back(mesh);
            return *this;
        }

        std::vector<Mesh>& GetObjects() {
            return objects;
        }

    };

}