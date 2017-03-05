#include "../hpp/scene.hpp"


namespace PantaRay {

    bool Scene::Intersect(const Ray& ray, Intersection& intersection) {
        auto closest_intersection = Intersection();
        closest_intersection.distance = Constants::inf;
        Mesh* closest_mesh = nullptr;

        for (auto& object : GetObjects()) {
            auto intersection = Intersection();
            if (object.geometry->Intersect(ray, intersection) &&
                intersection.distance < closest_intersection.distance) {
                closest_intersection = intersection;
                closest_mesh = &object;
            }
        }

        intersection = closest_intersection;
        intersection.mesh = closest_mesh;

        return true;
    }

}
