#pragma once

#include "vector.hpp"
#include "ray.hpp"
#include "shading.hpp"
#include "intersection.hpp"


namespace PantaRay {

    struct IGeometry {

        virtual bool Intersect(const Ray& ray, Intersection& intersection) = 0;

        virtual ~IGeometry() {}

    };

    struct PlaneGeometry : public IGeometry {

        Vector position;
        Vector normal;

        PlaneGeometry(const Vector& _position, const Vector& _normal) : position(_position), normal(_normal.Copy().Normalize()) {}

        bool Intersect(const Ray& ray, Intersection& intersection) {
            double denom = normal.Dot(ray.direction);

            if (fabs(denom) > Constants::eps) {
                double scalar = position.Subtract(ray.start).Dot(normal) / denom;
                if (scalar >= 0) {
                    intersection.distance = scalar;
                    intersection.normal = normal;
                    intersection.position = ray.ScaleTo(scalar);
                    intersection.u = intersection.position.x;
                    intersection.v = intersection.position.y;

                    return true;
                }
            }

            return false;
        }

    };

}