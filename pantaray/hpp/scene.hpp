#pragma once

#include <vector>

#include "mesh.hpp"
#include "light.hpp"


namespace PantaRay {

    class Scene : IGeometry {

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

        bool Intersect(const Ray& ray, Intersection& intersection);

        std::vector<Mesh>& GetObjects() {
            return objects;
        }

        std::vector<ILight*>& GetLights() {
            return lights;
        }

    };

}
