#pragma once

#include <math.h>

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

                    // TODO: Fix uv coords
                    intersection.u = intersection.position.x;
                    intersection.v = intersection.position.y;

                    return true;
                }
            }

            return false;
        }

    };

    struct SphereGeometry : public IGeometry {

        Vector position;
        double radius;

        SphereGeometry(Vector&& _position, double&& _radius) : position(_position), radius(_radius) {}

        bool Intersect(const Ray& ray, Intersection& intersection) {
            double a = ray.direction.LengthSqr();
            double b = ray.direction.Copy().Dot(ray.start.Copy().Subtract(position)) * 2;
            double c = ray.start.Copy().Subtract(position).LengthSqr() - radius * radius;
            double d = b * b - 4 * a * c;

            if (d > 0) {
                double x1 = (-b + sqrt(d)) / (2 * a);
                double x2 = (-b - sqrt(d)) / (2 * a);
                double min_x = x1 > x2 ? x2 : x1;

                if (min_x > 0) {
                    intersection.distance = min_x;
                    intersection.position = ray.start.Copy().Add(ray.direction.Copy().Scale(min_x));
                    intersection.normal = intersection.position.Copy().Subtract(position).Normalize();

                    auto normal_copy = intersection.normal.Copy();

                    intersection.u = (atan2(normal_copy.z, normal_copy.x) + Constants::pi) / (2 * Constants::pi);
                    intersection.v = (asin(normal_copy.y / radius) + Constants::pi / 2) / Constants::pi;

                    return true;
                }
            }

            return false;
        }

    };

}