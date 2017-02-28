#pragma once

#include <math.h>

#include "ray.hpp"
#include "intersection.hpp"


namespace PantaRay {

    struct IGeometry {

        virtual bool Intersect(const Ray& ray, Intersection& intersection) = 0;

        virtual ~IGeometry() {}

    };

    struct PlaneGeometry : public IGeometry {

        Vector position;
        Vector normal;

        PlaneGeometry(const Vector& _position, const Vector& _normal) :
            position(_position), normal(_normal.Copy().Normalize()) {
        }

        bool Intersect(const Ray& ray, Intersection& intersection);

    };

    struct SphereGeometry : public IGeometry {

        Vector position;
        float radius;

        SphereGeometry(Vector&& _position, float&& _radius) :
            position(_position), radius(_radius) {
        }

        bool Intersect(const Ray& ray, Intersection& intersection);

    };

}
