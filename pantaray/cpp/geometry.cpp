#include "../hpp/geometry.hpp"


namespace PantaRay {

    bool PlaneGeometry::Intersect(const Ray& ray, Intersection& intersection) {
        float denom = normal.Dot(ray.direction);

        if (fabs(denom) > Constants::eps) {
            float scalar = position.Copy().Subtract(ray.start).Dot(normal) / denom;
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

    bool SphereGeometry::Intersect(const Ray& ray, Intersection& intersection) {
        float a = ray.direction.LengthSqr();
        float b = ray.direction.Copy().Dot(ray.start.Copy().Subtract(position)) * 2;
        float c = ray.start.Copy().Subtract(position).LengthSqr() - radius * radius;
        float d = b * b - 4 * a * c;

        if (d > 0) {
            float x1 = float((-b + sqrt(d)) / (2 * a));
            float x2 = float((-b - sqrt(d)) / (2 * a));
            float min_x = x1 > x2 ? x2 : x1;

            if (min_x > 0) {
                intersection.distance = min_x;
                intersection.position = ray.ScaleTo(min_x);
                intersection.normal = intersection.position.Copy().Subtract(position).Normalize();

                auto normal_copy = intersection.normal.Copy();

                intersection.u = float((atan2(normal_copy.y, normal_copy.x) + Constants::pi) / (2 * Constants::pi));
                intersection.v = float(asin(normal_copy.z / radius) * Constants::pi);

                return true;
            }
        }

        return false;
    }

    bool DistanceEstimatorGeometry::Intersect(const Ray& ray, Intersection& intersection) {
        float total_distance = 0.0f;
        unsigned steps;

        for (steps = 0; steps < max_iterations; steps++) {
            auto marching_ray = ray.Copy().Translate(total_distance);
            float distance = distance_extimator(marching_ray.start);
            total_distance += distance;
            if (distance < epsilon_break) break;
        }

        intersection.distance = 1 - float(steps) / float(max_iterations);
        intersection.normal = total_distance;

        return true;
    }

}
