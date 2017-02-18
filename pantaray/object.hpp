#pragma once

#include "vector.hpp"
#include "ray.hpp"


namespace PantaRay {

    struct Intersection {

        Vector position;
        Vector normal;
        double distance;
        double u, v;
        bool valid;

    };

    struct IGeometry {

        virtual Intersection& Intersect(const Ray& ray, Intersection& intersection) = 0;

        virtual ~IGeometry() {}

    };

    struct Plane : public IGeometry{

        Vector position;
        Vector normal;

        Plane(const Vector& _position, const Vector& _normal) : position(_position), normal(_normal.Copy().Normalize()) {}

        Intersection& Intersect(const Ray& ray, Intersection& intersection) {
            intersection.valid = false;
            double denom = normal.Dot(ray.direction);

            if (fabs(denom) > Constants::eps) {
                double scalar = position.Subtract(ray.start).Dot(normal) / denom;
                if (scalar >= 0) {
                    intersection.valid = true;
                    intersection.distance = scalar;
                    intersection.normal = normal;
                    intersection.position = ray.ScaleTo(scalar);
                }
            }

            return intersection;
        }

    };

}