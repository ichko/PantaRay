#pragma once

#include <math.h>

#include "constants.hpp"

namespace PantaRay {

    struct Vector {

        double x, y, z;

        Vector(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}

        void MakeZero() {
            x = y = z = 0;
        }

        bool IsZero(double eps = Constants::eps) {
            return Length() < eps;
        }

        double LengthSqr() {
            return x * x + y * y + z * z;
        }

        double Length() {
            return sqrt(LengthSqr());
        }

        Vector& Scale(double factor) {
            x *= factor;
            y *= factor;
            z *= factor;

            return *this;
        }

        Vector& ScaleTo(double factor) {
            Normalize();
            return Scale(factor);
        }

        Vector& Add(const Vector& vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;

            return *this;
        }

        Vector& Subtract(const Vector& vector) {
            Add(vector.Copy().Reflect());

            return *this;
        }

        Vector& Reflect() {
            x = -x;
            y = -y;
            z = -z;

            return *this;
        }

        Vector Cross(const Vector& vector) {
            auto _x = y * vector.z - z * vector.y;
            auto _y = z * vector.x - x * vector.z;
            auto _z = z * vector.y - y * vector.x;

            x = _x;
            y = _y;
            z = _z;

            return *this;
        }

        double Dot(const Vector& vector) {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        Vector& Normalize() {
            double length = Length();
            x /= length;
            y /= length;
            z /= length;

            return *this;
        }

        Vector Copy() const {
            return Vector(x, y, z);
        }

    };

}